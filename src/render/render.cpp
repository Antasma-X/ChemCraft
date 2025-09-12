#include "render.h"

void Render::createCompoundObject(Compound* compound){

    if (!compound||compound->getAtoms().empty()){
        error->push("Invalid or empty compound being rendered");
        return;
    }

    ImGuiIO& io = ImGui::GetIO();

    std::set<Element*> visited;
    std::unordered_map<Element*, glm::vec2> positions;

    glm::vec2 origin = glm::vec2(0.0f);
    float spacing=elementTextureHeight*elementSpacingAmount;

    std::vector<glm::vec2> directions={
        {1, 0},   // right
        {0, 1},   // up
        {-1, 0},  // left
        {0, -1}   // down
    };

    std::queue<std::pair<Element*, glm::vec2>> q;
    Element* root=compound->getAtoms()[0];
    q.push({root,origin});
    positions[root]=origin;

    while (!q.empty()){
        auto [current, pos]=q.front();
        q.pop();

        if(visited.count(current)) continue;

        visited.insert(current);

        const auto& bondMap=compound->getBonds();
        auto it=bondMap.find(current);
        const auto& neighbors=it->second;
        int dirIndex=0;

        for(const auto& [neighbor, bondType]: neighbors){
            if(visited.count(neighbor)) continue;

            glm::vec2 offset=directions[dirIndex %directions.size()]*spacing;
            glm::vec2 neighborPos=pos+offset;

            if(positions.count(neighbor)==0){
                positions[neighbor]=neighborPos;
                q.push({neighbor, neighborPos});
            }

            dirIndex++;
        }
    }

    glm::vec2 minPos = positions.begin()->second;
    glm::vec2 maxPos = positions.begin()->second;

    for (const auto& [el, pos]: positions){
        minPos.x=std::min(minPos.x, pos.x);
        minPos.y=std::min(minPos.y, pos.y);
        maxPos.x=std::max(maxPos.x, pos.x);
        maxPos.y=std::max(maxPos.y, pos.y);
    }

    glm::vec2 compoundCenter=(minPos + maxPos)*0.5f;
    //glm::vec2 screenCenter=camera->GetCurrentPosition();
    glm::vec2 screenCenter=camera->GetCurrentPosition()+glm::vec2(io.DisplaySize.x*(1-sideMenuWidthPerCentCopy), io.DisplaySize.y) * 0.5f / camera->zoom;
    glm::vec2 shift=screenCenter -compoundCenter;

    std::vector<ElementObject*> updateEls;

    for(const auto& [el, pos]: positions){
        glm::vec2 finalPos=pos+shift;
        try{
            auto* obj=new ElementObject(finalPos, el);
            ElementObject::getAllElementObjects()[el]=obj;
            updateEls.push_back(obj);
            elementObjectToCompound[obj]=compound;
        } 
        catch (const std::exception& e) {
            error->push("Failed to create ElementObject: "+std::string(e.what()));
        }
    }
        auto bonds=compound->getBonds();

    for(auto& [el1, bondedList]: bonds){
        ElementObject* obj1=ElementObject::getAllElementObjects()[el1];
        if (!obj1) continue;

        for(auto& [el2,bondType]: bondedList ){
            if (el1 > el2) continue;

            ElementObject* obj2=ElementObject::getAllElementObjects()[el2];
            if (!obj2) continue;

            glm::vec2 bestA,bestB;
            float minDist=std::numeric_limits<float>::max();

            std::vector<glm::vec2> spots1,spots2;

            if(bondType==0){
                spots1=obj1->getElectronPositions();
                spots2=obj2->getElectronPositions();
            }
            else if(bondType==-1||bondType==1){
                spots1 ={obj1->getChargePosition()};
                spots2 ={obj2->getChargePosition()};
            }
            else if(bondType==-2||bondType==2){
                spots1 = obj1->getDativePositions();
                spots2 = obj2->getDativePositions();
            }
            else{
                error->push("Unknown bond type in compound");
            }

            for(const auto& p1: spots1){
                for(const auto& p2: spots2){
                    float dist=glm::distance(p1,p2);
                    if (dist<minDist){
                        minDist= dist;
                        bestA=p1;
                        bestB=p2;
                    }
                }
            }

            std::vector<glm::vec2> finalEnds;
            std::vector<ElementObject*> elements;

            if(bondType==1||bondType==-2){
                finalEnds={bestB,bestA};
                elements={obj2,obj1};
            } 
            else{
                finalEnds={bestA,bestB};
                elements={obj1,obj2};

            }

            try{
                auto bondObj=new BondObject(finalEnds, elements, std::abs(bondType));
                bondObjectToCompound[bondObj]=compound;
                compoundToBondObjects[compound].insert(bondObj);
            } 
            catch (const std::exception& e) {
                error->push("Failed to create BondObject: " + std::string(e.what()));
            }
        }
    }

    for(auto el:updateEls){
        el->update();
    }
    
    Render::compoundList.push_back(compound);
}

void Render::render(){

    //Elements and their electrons
    for(auto compound:compoundList){
        std::vector<Element*> atomList=compound->getAtoms();

        for(auto atom: atomList){

            if(ElementObject::getAllElementObjects()[atom]==nullptr){

                error->push("Element was not rendered. Please Destroy Compound Immediately");
                continue;
            }
            ElementObject::getAllElementObjects()[atom]->render();
        }
    }

    //Bonds
    for(auto it:BondObject::getAllBondObjects()){
        it->render();
    }
}

void Render::moveCompound(Compound* comp,glm::vec2 delta){

    std::vector<Element*> atomList=comp->getAtoms();
    for(auto atom: atomList){
        if(ElementObject::getAllElementObjects()[atom]==nullptr){
            error->push("Element was not found. Please Destroy Compound Immediately");
            
            continue;
        }
        ElementObject::getAllElementObjects()[atom]->move(delta);
        moveBonds(ElementObject::getAllElementObjects()[atom],delta);
    }
}

void Render::moveBonds(ElementObject* el,glm::vec2 delta){
    for (auto& bond: BondObject::getAllBondObjects()){
        if (bond->getElements()[0]==el){
            bond->move(delta,0);
        }

        if (bond->getElements()[1]==el){
            bond->move(delta,1);
        }
    }
} 

void Render::moveDative(ElectronObject* dative,glm::vec2 delta){
    auto electrons=ElementObject::getElectronsOfDative(dative);
    if(!electrons[0]||!electrons[1]||electrons[0]->isTransparent()||electrons[1]->isTransparent()){
        return;
    }
    dative->move(delta);

    glm::vec2 dativePos = dative->getPosition();
    glm::vec2 elementCenter = ElementObject::getElementObjectOfElectronOrDative(dative)->getPosition(); // You need access to this

    // Vector from element to dative
    glm::vec2 dir = dativePos - elementCenter;
    float len = glm::length(dir);
    if (len == 0) return;
  
    float electronSeparation = std::max(elementTextureHeight-2*electronDistanceAdjust - len * electronToDativePullFactor, minElectronSeparation);
    glm::vec2 offset = dir * (electronSeparation / 2.0f);

    electrons[0]->move(delta+offset);
    electrons[1]->move(delta-offset);
}

int Render::checkElectronShiftingOrBonding(ElectronObject* electron){

    glm::vec2 pos=electron->getPosition();

    ElectronObject* otherElectron=nullptr;
    ElementObject* otherChargeElementObject=nullptr;
 
    for (auto& el : ElementObject::getAllElementObjects()){
        std::vector<ElectronObject*> newObjs=el.second->getElectronObjectsOn(pos);
        bool loopOver=false;
        if(!newObjs.empty()){
            for(auto it: newObjs){
                if(it!=electron){
                    otherElectron=it;
                    loopOver=true;
                    break;
                }
            }
        }
        if(loopOver){
            break;
        }
    }

    for (auto& el : ElementObject::getAllElementObjects()){
        if(el.second->chargeObjectContains(pos)){
            if(el.second!=ElementObject::getElementObjectOfElectronOrDative(electron)){
                otherChargeElementObject=el.second;
                break;
            }
        }
    }

    if(otherElectron!=nullptr){
        if(ElementObject::getElementObjectOfElectronOrDative(electron)==ElementObject::getElementObjectOfElectronOrDative(otherElectron)){
            if(electron==otherElectron){
                return 0;
            }
            ElementObject::getElementObjectOfElectronOrDative(electron)->shiftElectronToNewElectron(electron,otherElectron);
            return 1;
        }
        else if(otherElectron->isTransparent()){
            if(createBond(ElementObject::getElementObjectOfElectronOrDative(electron),ElementObject::getElementObjectOfElectronOrDative(otherElectron),0,electron,otherElectron)==0){
                return -1;
            }
            return 2;
        } 
    }
    else if(otherChargeElementObject!=nullptr){
        if(createBond(ElementObject::getElementObjectOfElectronOrDative(electron),otherChargeElementObject,electron)==0){
            return -1;
        }
        return 3;
    }

    return 0;
}

int Render::checkDativeBonding(ElectronObject* dative){
    ElectronObject* otherDative=nullptr;

    for (auto& el : ElementObject::getAllElementObjects()){
        std::vector<ElectronObject*> newObjs=el.second->getDativeObjectsOn(dative->getPosition());
        if(!newObjs.empty()){
            otherDative=newObjs[0];
            break;
        }
    }

    if(otherDative==nullptr){
        return 0;
    }

    if(ElementObject::getElementObjectOfElectronOrDative(dative)==ElementObject::getElementObjectOfElectronOrDative(otherDative)){
        return 0;
    }
    else{
        if(createBond(ElementObject::getElementObjectOfElectronOrDative(dative),ElementObject::getElementObjectOfElectronOrDative(otherDative),2,dative,otherDative)==0){
            return -1;
        }
        return 1;
    }
}

int Render::createBond(ElementObject* elObj1,ElementObject* elObj2, int type, ElectronObject* electron, ElectronObject* otherElectron){
    
    if(!elObj1||!elObj2){
        return 0;
    }
    
    Compound* comp1=elementObjectToCompound[elObj1];
    Compound* comp2=elementObjectToCompound[elObj2];

    if(comp1==comp2){
        if(!comp1->createBond(*elObj1->getElement(),*elObj2->getElement(),type)){
            return 0;
        }

        BondObject* bondObject = new BondObject({elObj1->getOriginalElectronOrDativePosition(electron),otherElectron->getPosition()},{elObj1,elObj2},-type);
        bondObjectToCompound[bondObject]=comp1;
        compoundToBondObjects[comp1].insert(bondObject);

        elObj1->update();
        elObj2->update();
    }
    else{
        if(!comp1->addElement(*elObj1->getElement(),*elObj2->getElement(),*comp2,-type)){
            return 0;
        }

        BondObject* bondObject = new BondObject({elObj1->getOriginalElectronOrDativePosition(electron),otherElectron->getPosition()},{elObj1,elObj2},type);

        bondObjectToCompound[bondObject]=comp1;
        compoundToBondObjects[comp1].insert(bondObject);

        elObj1->update();
        elObj2->update();

        auto it = std::find(compoundList.begin(), compoundList.end(), comp2);
        if (it != compoundList.end()) {
            compoundList.erase(it);
        }

        for(auto& [key,value]: bondObjectToCompound){
            if(value==comp2){
                bondObjectToCompound[key]=comp1;
            }
        }

        compoundToBondObjects[comp1].insert(compoundToBondObjects[comp2].begin(),compoundToBondObjects[comp2].end());
        compoundToBondObjects.erase(comp2);

        for(auto& [key,value]:elementObjectToCompound){
            if(value==comp2){
                elementObjectToCompound[key]=comp1;
            }
        }

        delete comp2;
    }
    return 1;
}

int Render::createBond(ElementObject* elObj1,ElementObject* elObj2, ElectronObject* electron){
    Compound* comp1=elementObjectToCompound[elObj1];
    Compound* comp2=elementObjectToCompound[elObj2];

    if(comp1==comp2){
        if(!comp1->createBond(*elObj1->getElement(),*elObj2->getElement(),-1)){
            return 0;
        }

        BondObject* bondObject = new BondObject({elObj1->getChargePosition(),elObj2->getChargePosition()},{elObj1,elObj2},1);
        bondObjectToCompound[bondObject]=comp1;
        compoundToBondObjects[comp1].insert(bondObject);

        elObj1->update();
        elObj2->update();
    }  
    else{
        if(!comp1->addElement(*elObj1->getElement(),*elObj2->getElement(),*comp2,-1)){
            return 0;
        }

        BondObject* bondObject = new BondObject({elObj1->getChargePosition(),elObj2->getChargePosition()},{elObj1,elObj2},1);
        bondObjectToCompound[bondObject]=comp1;
        compoundToBondObjects[comp1].insert(bondObject);
        
        elObj1->update();
        elObj2->update();

        auto it = std::find(compoundList.begin(), compoundList.end(), comp2);
        if (it != compoundList.end()) {
            compoundList.erase(it);
        }

        for(auto [key,value]: bondObjectToCompound){
            if(value==comp2){
                bondObjectToCompound[key]=comp1;
            }
        }

        compoundToBondObjects[comp1].insert(compoundToBondObjects[comp2].begin(),compoundToBondObjects[comp2].end());
        compoundToBondObjects.erase(comp2);

        for(auto [key,value]:elementObjectToCompound){
            if(value==comp2){
                elementObjectToCompound[key]=comp1;
            }
        }
        
        delete comp2;
    }

    return 1;
}

int Render::removeBond(BondObject* bondObj){

    if(!bondObj){
        return 0;
    }

    Compound* comp=bondObjectToCompound[bondObj];

    auto stackCompounds=comp->removeBond(*bondObj->getElements()[0]->getElement(),*bondObj->getElements()[1]->getElement(),bondObj->getType());
    
    if(stackCompounds.size()==0){
        return 0; 
    }

    bondObj->getElements()[0]->update();
    bondObj->getElements()[1]->update();

    if(stackCompounds.size()==2){

        std::vector<Compound*> compounds;
        for(auto& sComp:stackCompounds){
            compounds.push_back(new Compound(sComp));
        }

        auto it = std::find(compoundList.begin(), compoundList.end(), comp);
        if (it != compoundList.end()) {
            compoundList.erase(it);
        }

        compoundList.push_back(compounds[0]);
        compoundList.push_back(compounds[1]);

        //bondObjectToCompound
        auto atomList=compounds[0]->getAtoms();
        for(auto it=bondObjectToCompound.begin();it!=bondObjectToCompound.end();++it){
            if (it->second==comp){
                auto it2 = std::find(atomList.begin(), atomList.end(), it->first->getElements()[0]->getElement());
                if (it2 != atomList.end()) {
                    it->second=compounds[0];
                }
                else{
                    it->second=compounds[1];
                }
            }
        }

        //compoundToBondObject
        compoundToBondObjects[comp].erase(bondObj);
        auto copy=compoundToBondObjects[comp];
        for(auto bondObject: copy){
            auto it = std::find(atomList.begin(), atomList.end(), bondObject->getElements()[0]->getElement());
            if (it != atomList.end()) {
                compoundToBondObjects[compounds[0]].insert(bondObject);
            }
            else{
                compoundToBondObjects[compounds[1]].insert(bondObject);
            }
        }
        compoundToBondObjects.erase(comp);

        //elementObjectToCompound
        for(auto it=elementObjectToCompound.begin();it!=elementObjectToCompound.end();++it){
            if (it->second==comp){
                auto it2 = std::find(atomList.begin(), atomList.end(), it->first->getElement());
                if (it2 != atomList.end()) {
                    it->second=compounds[0];
                }
                else{
                    it->second=compounds[1];
                }
            }
        }
        delete comp;
    }
    else{
        compoundToBondObjects[comp].erase(bondObj);
    }
    
    bondObjectToCompound.erase(bondObj);
    delete bondObj;

    return 1;
}

int Render::removeElement(ElementObject* elementObj){
    Compound* comp=elementObjectToCompound[elementObj];
 
    auto stackCompounds=comp->removeElement(*elementObj->getElement());

    std::vector<Compound*> compounds;
    if(stackCompounds.size()==2){
        for(auto& sComp:stackCompounds){
            compounds.push_back(new Compound(sComp));
        } 
    }

    //get all the bondobjs the element was connected to
    std::vector<BondObject*> bondObjectsToBeRemoved;
    std::vector<ElementObject*> elementObjectsToBeUpdated;

    for(auto bondObj: BondObject::getAllBondObjects()){
        if(elementObj==bondObj->getElements()[0]){
            elementObjectsToBeUpdated.push_back(bondObj->getElements()[1]);
            bondObjectsToBeRemoved.push_back(bondObj);
        }
        else if(elementObj==bondObj->getElements()[1]){
            elementObjectsToBeUpdated.push_back(bondObj->getElements()[0]);
            bondObjectsToBeRemoved.push_back(bondObj);
        }
    }

    if(compounds.size()>=2){

        auto it = std::find(compoundList.begin(), compoundList.end(), comp);
        if (it != compoundList.end()) {
            compoundList.erase(it);
        }

        for(auto it:compounds){
            compoundList.push_back(it);
        }

        for(auto it=bondObjectToCompound.begin();it!=bondObjectToCompound.end();){
            if(it->second==comp){
                if(std::find(bondObjectsToBeRemoved.begin(),bondObjectsToBeRemoved.end(),it->first)!=bondObjectsToBeRemoved.end()){
                    it=bondObjectToCompound.erase(it);
                    continue;
                }
                for(auto compound:compounds){
                    auto atomList=compound->getAtoms();
                    auto it2 = std::find(atomList.begin(), atomList.end(), it->first->getElements()[0]->getElement());
                    if (it2 != atomList.end()) {
                        it->second=compound;
                        break;
                    }
                }
            }
            it++;
        }

        for(auto bondObject:compoundToBondObjects[comp]){
            if(std::find(bondObjectsToBeRemoved.begin(),bondObjectsToBeRemoved.end(),bondObject)!=bondObjectsToBeRemoved.end()){
                bondObjectToCompound.erase(bondObject);
                continue;
            }
//basically we have to find wht each bond object belongs to add there

            for(auto compound:compounds){
                auto atomList=compound->getAtoms();
                auto it = std::find(atomList.begin(), atomList.end(), bondObject->getElements()[0]->getElement());
                if (it != atomList.end()) {
                    compoundToBondObjects[compound].insert(bondObject);
                    break;
                }
            }
        }
        compoundToBondObjects.erase(comp);

        elementObjectToCompound.erase(elementObj); 

        for(auto it=elementObjectToCompound.begin();it!=elementObjectToCompound.end();){
            if (it->second==comp){
                for(auto compound:compounds){
                    auto atomList=compound->getAtoms();
                    auto it2 = std::find(atomList.begin(), atomList.end(), it->first->getElement());
                    if (it2 != atomList.end()) {
                        it->second=compound;
                        break;
                    }
                }
            }
        }

        delete comp;
    }

    for(auto bondObj: bondObjectsToBeRemoved){
        delete bondObj;
    }

    for(auto elObj:elementObjectsToBeUpdated){
        elObj->update();
    }

    elementObjectToCompound.erase(elementObj);
    delete elementObj;

    return 1;
}

void Render::deleteCompound(Compound* comp){

    if(!comp){
        return;
    }

    //Compound List
    bool isInList=false;
    for(auto it = compoundList.begin(); it != compoundList.end();){
        if(*it == comp){
            it=compoundList.erase(it);
            isInList=true;
            break;
        }
        else{
            it++;
        }
    }

    if(!isInList){
        return;
    }

    //ElementObjectToCompound
    std::vector<Element*> atomList=comp->getAtoms();
    
    for(auto& atom: atomList){

        auto elObj=ElementObject::getAllElementObjects()[atom];
        if(elObj==nullptr){
            error->push("Element was not rendered. Please Destroy Compound Immediately");
            continue;
        }

        delete elObj;
        elementObjectToCompound.erase(elObj);
        delete atom;
    }   

    //bondObjectToCompound
    //compoundToBondObject 

    for(auto& bond: compoundToBondObjects[comp]){
        if(bondObjectToCompound.find(bond)!=bondObjectToCompound.end()){
            bondObjectToCompound.erase(bond);
        }
        delete bond;
    }
    compoundToBondObjects.erase(comp);



    //ChatGPT said
    // Defensive cleanup: purge any lingering mappings that still reference this comp
    for (auto it = bondObjectToCompound.begin(); it != bondObjectToCompound.end(); ){
        if (it->second == comp) it = bondObjectToCompound.erase(it); // FIX: iterator-safe erase
        else ++it;
    }
    for (auto it = elementObjectToCompound.begin(); it != elementObjectToCompound.end(); ){
        if (it->second == comp) it = elementObjectToCompound.erase(it); // FIX: iterator-safe erase
        else ++it;
    }
    compoundToBondObjects.erase(comp);  

    delete comp;
}

void Render::resetElectronPos(ElectronObject* electron){
    ElementObject* elObj =ElementObject::getElementObjectOfElectronOrDative(electron);

    glm::vec2 ogPos=elObj->getOriginalElectronOrDativePosition(electron);
    electron->move(ogPos-electron->getPosition());
}

void Render::resetDativePos(ElectronObject* dative){
    ElementObject* elObj =ElementObject::getElementObjectOfElectronOrDative(dative);

    std::array<ElectronObject*,2> electrons=ElementObject::getElectronsOfDative(dative);

    glm::vec2 ogPos;

    ogPos=elObj->getOriginalElectronOrDativePosition(dative);
    dative->move(ogPos-dative->getPosition());

    ogPos=elObj->getOriginalElectronOrDativePosition(electrons[0]);
    electrons[0]->move(ogPos-electrons[0]->getPosition());

    ogPos=elObj->getOriginalElectronOrDativePosition(electrons[1]);
    electrons[1]->move(ogPos-electrons[1]->getPosition());
}

bool Render::isPartOfOneCompound(std::set<ElementObject*> elementObjects){

    for(auto compound:compoundList){
        auto atoms=compound->getAtoms();
        if (elementObjects.size() != atoms.size()){
            continue;
        }

        std::unordered_set<Element*> setA;

        for(auto el: elementObjects){
            setA.insert(el->getElement());
        }

        std::unordered_set<Element*> setB;

        for(auto el: atoms){
            setB.insert(el);
        }

        if(setA==setB){
            return true;
        }
    }

    return false;
}


Compound* Render::getCompoundIfExists(std::set<ElementObject*> elementObjects){
    Compound* comp=nullptr;

    for(auto compound:compoundList){
        auto atoms=compound->getAtoms();
        if (elementObjects.size() != atoms.size()){
            continue;
        }

        std::unordered_set<Element*> setA;

        for(auto el: elementObjects){
            setA.insert(el->getElement());
        }

        std::unordered_set<Element*> setB;

        for(auto el: atoms){
            setB.insert(el);
        }

        if(setA==setB){
            comp=compound;
            break;
        }
    }

    return comp;
}

std::set<ElementObject*> Render::getElementObjectsOn(glm::vec2 pos){
    std::set<ElementObject*> objs;

    for (auto& el : ElementObject::getAllElementObjects()){
        if(el.second->contains(pos)){
            objs.insert(el.second);
        }
    }
    return objs;
}

std::set<ElectronObject*> Render::getElectronObjectsOn(glm::vec2 pos){
    std::set<ElectronObject*> objs;
    //only when selecting is happeneing element loses ownership of electron
    for (auto& el : ElementObject::getAllElementObjects()){
        std::vector<ElectronObject*> newObjs=el.second->getElectronObjectsOn(pos);
        objs.insert(newObjs.begin(),newObjs.end());
    }
    return objs;
}

std::set<ElectronObject*> Render::getDativeObjectsOn(glm::vec2 pos){
    std::set<ElectronObject*> objs;
    //only when selecting is happeneing element loses ownership of electron
    for (auto& el : ElementObject::getAllElementObjects()){
        std::vector<ElectronObject*> newObjs=el.second->getDativeObjectsOn(pos);
        objs.insert(newObjs.begin(),newObjs.end());
    }
    return objs;
}

std::set<BondObject*> Render::getBondsObjectsOn(glm::vec2 pos){
    std::set<BondObject*> objs;

    for (auto& bond : BondObject::getAllBondObjects()){
        if(bond->contains(pos)){
            objs.insert(bond);
        }
    }
    return objs;
}

Compound* Render::getCompoundSelected(glm::vec2 pos){
 
    for(auto comp :compoundList ){
        auto atomList=comp->getAtoms();
        for(auto atom:atomList){
            auto obj=ElementObject::getAllElementObjects()[atom];
            if(obj==nullptr){
                continue;
            }
            if(obj->contains(pos)){
                return comp;
            }
        } 
    }
    return nullptr;
} 

Compound* Render::getCompoundWithElementObject(ElementObject* elObj){
    return elementObjectToCompound[elObj];
}

std::set<ElementObject*> Render::getCompoundElementObjectsWithBondObject(BondObject* bondObj){
    std::set<ElementObject*> elObjs;
    
    Compound* comp=bondObjectToCompound[bondObj];

    std::vector<Element*> atomList=comp->getAtoms();
    for(auto atom: atomList){

        if(ElementObject::getAllElementObjects()[atom]==nullptr){
            error->push("Element was not found. Please Destroy Compound Immediately");
            continue;
        }
        elObjs.insert(ElementObject::getAllElementObjects()[atom]);
    }

    return elObjs;
}

std::set<BondObject*> Render::getCompoundBondObjectsWithElementObject(ElementObject* elObj){
    std::set<BondObject*> bondObjs;
    Compound* comp=elementObjectToCompound[elObj];

    return compoundToBondObjects[comp];
}

std::vector<Compound*> Render::getCompoundList(){
    return compoundList;
}
