#include "elementObject.h"

std::map<Element*,ElementObject*> ElementObject::elementObjects={};

std::map<ElectronObject*,std::array<ElectronObject*,2>> ElementObject::dativeToElectrons={};

std::map<ElectronObject*,ElementObject*> ElementObject::electronOrDativeToElementObject={};

void ElementObject::generateElectrons(){

    int n=element->getNumberOfValenceElectrons();
    GLfloat transparency=1.0f;

    for(int i=0;i<8;i++){
        glm::vec2 pos;

        if(i==n){
            transparency=0.0f;
        }

        if(i==0){
            pos={
               position[0]-width/2-electronDistanceDirect,position[1]-elementTextureHeight/2+electronDistanceAdjust 
            };
        }
        else if(i==1){
            pos={
                position[0]+ width/2+electronDistanceDirect,position[1]+elementTextureHeight/2-electronDistanceAdjust 
            };         
        }
        else if(i==2){ 
            pos={
                position[0]-width/2+electronDistanceAdjust,position[1]+elementTextureHeight/2+electronDistanceDirect 
            };         
        }
        else if(i==3){
            pos={
                position[0]+width/2-electronDistanceAdjust,position[1]-elementTextureHeight/2-electronDistanceDirect 
            };         
        }
        else if(i==4){
            pos={
                position[0]-width/2-electronDistanceDirect,position[1]+elementTextureHeight/2-electronDistanceAdjust 
            };
        }
        else if(i==5){
            pos={
                position[0]+width/2-electronDistanceAdjust,position[1]+elementTextureHeight/2+electronDistanceDirect 
            };         
        }
        else if(i==6){
            pos={
                position[0]+width/2+electronDistanceDirect,position[1]-elementTextureHeight/2+electronDistanceAdjust 
            };         
        }
        else if(i==7){
            pos={
                position[0]-width/2+electronDistanceAdjust,position[1]-elementTextureHeight/2-electronDistanceDirect 
            };
        }
        else{
            throw std::runtime_error("Electron Generation went Wrong");
        }
        electrons[i]=ElectronObject(pos,transparency);
        electronOrDativeToElementObject[&electrons[i]]=this;
    }
}

void ElementObject::generateDatives(){
    for(int i=0;i<4; i++){
        glm::vec2 pos;

        if(i==0){
            pos={
                position[0]-width/2-electronDistanceDirect,position[1]
            };
        }
        else if(i==1){
            pos={
                position[0],position[1]+elementTextureHeight/2+electronDistanceDirect
            };
        }
        else if(i==2){
            pos={
                position[0]+width/2+electronDistanceDirect,position[1]
            };
        }
        else if(i==3){
            pos={
                position[0],position[1]-elementTextureHeight/2-electronDistanceDirect
            };
        }
        else{
            throw std::runtime_error("Dative Generation went Wrong");
        }
        datives[i]=ElectronObject(pos,0.0f);

        //Thank you chatgpt
        if (i == 0) { // Left
            dativeToElectrons[&datives[i]] = { &electrons[0], &electrons[4] };
        }
        else if (i == 1) { // Top
            dativeToElectrons[&datives[i]] = { &electrons[3], &electrons[7] };
        }
        else if (i == 2) { // Right
            dativeToElectrons[&datives[i]] = { &electrons[1], &electrons[6] };
        }
        else if (i == 3) { // Bottom
            dativeToElectrons[&datives[i]] = { &electrons[2], &electrons[5] };
        }

        electronOrDativeToElementObject[&datives[i]]=this;
    }
}
 
void ElementObject::generateCharge(){
    //idk why i dont divide by 2 but fine
    glm::vec2 chargePos={position[0]+width/2,position[1]-elementTextureHeight/2};
    charge=ChargeObject(chargePos,element->getCharge());
}

void ElementObject::updateElectronShift() {
    if (!isShifting) return;

    double currentTime = glfwGetTime();
    float dt = (lastShiftUpdateTime == 0.0) ? 0.0f
                                           : static_cast<float>(currentTime - lastShiftUpdateTime);
    lastShiftUpdateTime = currentTime;

    shiftTimer += dt;
    float t = std::clamp(shiftTimer / electronShiftDuration, 0.0f, 1.0f);
    // ease-out cubic
    float easedT = 1.0f - pow(1.0f - t, 3.0f);

    glm::vec2 startPos = shiftStartPos;
    glm::vec2 endPos   = shiftEndPos;
    glm::vec2 newPos;

    // check if this is a straight shift (same x or same y)
    if (fabs(startPos.x - endPos.x) < 1e-3f || fabs(startPos.y - endPos.y) < 1e-3f) {
        newPos = glm::mix(startPos, endPos, easedT);
    } else {
        // --- Corner case: move along an arc around the correct rectangle corner ---
        glm::vec2 corner1 = { startPos.x, endPos.y };
        glm::vec2 corner2 = { endPos.x, startPos.y };

        // pick the corner closer to the element center
        glm::vec2 corner = (glm::distance(corner1, position) <
                            glm::distance(corner2, position)) ? corner1 : corner2;

        glm::vec2 dirA = startPos - corner;
        glm::vec2 dirB = endPos   - corner;

        float angleA = atan2(dirA.y, dirA.x);
        float angleB = atan2(dirB.y, dirB.x);
        float delta  = angleB - angleA;

        const float PI = 3.14159265358979323846f;
        while (delta >  PI) delta -= 2.0f * PI;
        while (delta < -PI) delta += 2.0f * PI;

        float theta = angleA + delta * easedT;
        float radius = glm::length(dirA);

        newPos = corner + glm::vec2(cos(theta), sin(theta)) * radius;
    }

    // move the visual electron
    electrons[shiftingFrom].move(newPos - electrons[shiftingFrom].getPosition());

    // ---- completion ----
    if (t >= 1.0f) {
        auto& fromElectron = electrons[shiftingFrom];
        auto& toElectron   = electrons[shiftingTo];

        if (toElectron.isTransparent()) {
            // Case 1: landed in empty → finalize
            toElectron.setTransparency(1.0f);
            fromElectron.setTransparency(0.0f);
            fromElectron.move(shiftEndPos - fromElectron.getPosition());

            isShifting   = false;
            shiftingFrom = shiftingTo = -1;
            shiftTimer   = 0.0f;
            return;
        } else {
            // Case 2: landed on occupied → swap
            int fromIdx = shiftingFrom;
            int toIdx   = shiftingTo;

            // snap to end
            electrons[fromIdx].move(shiftEndPos - electrons[fromIdx].getPosition());
            std::swap(electrons[fromIdx], electrons[toIdx]);

            // snap both anchors
            glm::vec2 toAnchor   = getOriginalElectronOrDativePosition(&electrons[toIdx]);
            glm::vec2 fromAnchor = getOriginalElectronOrDativePosition(&electrons[fromIdx]);
            electrons[toIdx].move(toAnchor - electrons[toIdx].getPosition());
            electrons[toIdx].setTransparency(1.0f);
            electrons[fromIdx].move(fromAnchor - electrons[fromIdx].getPosition());
            electrons[fromIdx].setTransparency(1.0f);

            // compute next target
            int nextTo = (toIdx + 1) % 8;

            // stop if we’ve come full circle (back to the latest toIdx)
            if (nextTo == shiftingFrom) {
                isShifting   = false;
                shiftingFrom = shiftingTo = -1;
                shiftTimer   = 0.0f;
                return;
            }

            // otherwise continue the chain
            shiftingFrom    = fromIdx;
            shiftingTo      = nextTo;
            shiftStartPos   = electrons[shiftingFrom].getPosition();
            shiftEndPos     = getOriginalElectronOrDativePosition(&electrons[shiftingTo]);
            shiftTimer      = 0.0f;
            lastShiftUpdateTime = glfwGetTime();
            isShifting      = true;
            return;
        }
    }
}

ElementObject::ElementObject(glm::vec2 pos, Element* el){

    if(el->getSymbol().size()==1){
        width=elementSingleTextureWidth;
    }
    else if(el->getSymbol().size()==2){
        width=elementDoubleTextureWidth;
    } 
    else{ 
        throw std::runtime_error("Atomic Symbol is Incorrect");
    }     
    
    vertices={
        -1.0f,-1.0f,0.0,0.0,
        -1.0f,1.0f,0.0,1.0,
        1.0f,1.0f,1.0,1.0,
        1.0f,-1.0f,1.0,0.0
    };

    std::vector<GLuint> indices={
        0,1,2,
        2,3,0 
    };

    element=el;
    this->position=pos;
    isSelected=false;
    isHovered=false;
    zIndex=Z_NORMAL;
 
    shaderProgram=shaders["element"]; 
    glowShaderProgram=shaders["glowElement"];

    vao=VAO();
    vao.Bind();
    vbo=VBO(vertices);
    ebo=EBO(indices);
    
    vao.LinkVBO(vbo,0,2,GL_FLOAT,4*sizeof(GLfloat),0);
    vao.LinkVBO(vbo,1,2,GL_FLOAT,4*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();

    texture=Texture(elementFilePath1+std::to_string(el->getAtomicNumber())+elementFilePath2);

    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(width/2.0f,elementTextureHeight/2.0f,1.0f));

    try{
        generateElectrons();
        generateDatives();
        generateCharge();
    }
    catch(std::runtime_error& e){
        throw;
    } 

    elementObjects[element]=this;
}  

ElementObject::ElementObject(ElementObject&& other) noexcept{
    vertices=std::move(other.vertices);
    vao=std::move(other.vao);
    vbo=std::move(other.vbo);
    ebo=std::move(other.ebo);
    texture=std::move(other.texture);
    shaderProgram=other.shaderProgram;
    glowShaderProgram=other.glowShaderProgram;

    position=other.position;
    model=other.model;

    element=other.element;
    width=other.width;
    isSelected=other.isSelected;
    isHovered=other.isHovered;
    zIndex=other.zIndex;
    
    electronAnimationProgress=other.electronAnimationProgress;
    isShifting=other.isShifting;
    shiftingFrom=other.shiftingFrom;
    shiftingTo=other.shiftingTo;
    shiftTimer=other.shiftTimer;
    shiftStartPos=other.shiftStartPos;
    shiftEndPos=other.shiftEndPos;
    lastShiftUpdateTime=other.lastShiftUpdateTime; 

    for(int i=0;i<8;i++){
        electrons[i]=std::move(other.electrons[i]);
    }

    for(int i=0;i<4;i++){
        datives[i]=std::move(other.datives[i]);
    }

    charge=std::move(other.charge);
    other.element=nullptr;
    elementObjects[element]=this;
}

ElementObject& ElementObject::operator=(ElementObject&& other) noexcept{
    if(this!=&other){
        vertices=std::move(other.vertices);
        vao=std::move(other.vao);
        vbo=std::move(other.vbo);
        ebo=std::move(other.ebo);
        texture=std::move(other.texture);
        shaderProgram=other.shaderProgram;
        glowShaderProgram=other.glowShaderProgram;
        position=other.position;
        model=other.model;

        element=other.element;
        width=other.width;
        isSelected=other.isSelected;
        isHovered=other.isHovered;
        zIndex=other.zIndex;

        electronAnimationProgress=other.electronAnimationProgress;
        isShifting=other.isShifting;
        shiftingFrom=other.shiftingFrom;
        shiftingTo=other.shiftingTo;
        shiftTimer=other.shiftTimer;
        shiftStartPos=other.shiftStartPos;
        shiftEndPos=other.shiftEndPos;
        lastShiftUpdateTime=other.lastShiftUpdateTime; 
        
        for(int i=0;i<8;i++){
            electrons[i]=std::move(other.electrons[i]);
        } 

        for(int i=0;i<4;i++){
            datives[i]=std::move(other.datives[i]);
        }

        charge=std::move(other.charge);

        other.element=nullptr;
        elementObjects[element]=this;
    }
    return *this;
}

ElementObject::~ElementObject(){
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    texture.Delete();

    elementObjects.erase(element);
    for(auto& dative:datives){
        dativeToElectrons.erase(&dative);
        electronOrDativeToElementObject.erase(&dative);
    }

    for(auto& electron:electrons){
        electronOrDativeToElementObject.erase(&electron);
    }
} 

void ElementObject::render(){

    if(isSelected||isHovered){
        glm::mat4 glowModel = glm::translate(glm::mat4(1.0f), glm::vec3(position, zIndex));
        glowModel = glm::scale(glowModel, glm::vec3(width * 1.1f, elementTextureHeight * 1.1f, 1.0f));

        glowShaderProgram.Activate();

        glowShaderProgram.SetMat4Uniform(glowModel, "model");
        glowShaderProgram.SetMat4Uniform(camera->GetView(), "view");
        glowShaderProgram.SetMat4Uniform(camera->GetProj(), "proj");
        if(isSelected){
            glowShaderProgram.Set1fUniform(elementSelectedGlowLevel, "glow");
        }
        else if(isHovered){
            glowShaderProgram.Set1fUniform(elementHoveredGlowLevel, "glow");
        }

        vao.Bind();

        glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

        vao.UnBind();
        glowShaderProgram.Deactivate();
    }

    shaderProgram.Activate();

    shaderProgram.SetMat4Uniform(model,"model");
    shaderProgram.SetMat4Uniform(camera->GetView(),"view");
    shaderProgram.SetMat4Uniform(camera->GetProj(),"proj");

    vao.Bind();
    texture.BindAndSetTexUnit(shaderProgram,"ourTexture");

    glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

    vao.UnBind();
    shaderProgram.Deactivate(); 
    texture.UnBind();

    updateElectronShift();

    for(auto& electron:electrons){
        electron.render();
    }

    for(auto& dative:datives){
        dative.render();
    }

    if(element->getCharge()!=0){
        charge.render();
    }
}

void ElementObject::move(glm::vec2 delta){
    position+=delta;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(width/2.0f,elementTextureHeight/2.0f,1.0f));

    for(auto& electron:electrons){
        electron.move(delta);
    }

    for(auto& dative:datives){
        dative.move(delta);
    }

    if(element->getCharge()!=0){
        charge.move(delta);
    }
}

bool ElementObject::contains(glm::vec2 pos){
    if (pos.x >= position.x - width/2.0f && pos.x <= position.x + width/2.0f &&
        pos.y >= position.y - elementTextureHeight/2.0f && pos.y <= position.y + elementTextureHeight/2.0f
    ){
        return true;
    }
    return false;
}

bool ElementObject::chargeObjectContains(glm::vec2 pos){
    return charge.contains(pos);
}

void ElementObject::select(bool b){
    isSelected=b;

    if(isSelected){
        zIndex=Z_SELECTED;
    }
    else{
        if(!isHovered){
            zIndex=Z_NORMAL;
        }
    }

    for(auto& electron: electrons){
        electron.shift(zIndex);
    }

    for(auto& dative: datives){
        dative.shift(zIndex);
    }

    charge.shift(zIndex);

    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(width/2.0f,elementTextureHeight/2.0f,1.0f));
}

void ElementObject::hover(bool b){
    isHovered=b;

    if(!isSelected){
        if(isHovered){
            zIndex=Z_HOVERED;
        }
        else{
            zIndex=Z_NORMAL;
        }
    }
    
    for(auto& electron: electrons){
        electron.shift(zIndex);
    }

    for(auto& dative: datives){
        dative.shift(zIndex);
    }

    charge.shift(zIndex);

    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(width/2.0f,elementTextureHeight/2.0f,1.0f));
}

void ElementObject::shiftElectronToNewElectron(ElectronObject* electron, ElectronObject* otherElectron) {

    int electronI = -1;
    int otherElectronI = -1;

    for (int i = 0; i < 8; ++i) {
        if (&electrons[i] == electron) electronI = i;
        if (&electrons[i] == otherElectron) otherElectronI = i;
    }

    if (electronI == -1 || otherElectronI == -1) {
        std::cerr << "[shift] invalid indices: electronI=" << electronI
                  << " otherElectronI=" << otherElectronI
                  << " electronPtr=" << electron << " otherPtr=" << otherElectron << "\n";
        return;
    }
    if (electronI == otherElectronI) {
        std::cerr << "[shift] ignored: same slot requested\n";
        return;
    }

    shiftingFrom = electronI;
    shiftingTo   = otherElectronI;
    shiftTimer   = 0.0f;
    isShifting   = true;

    // Capture fixed start/end positions for the animation
    shiftStartPos = electrons[shiftingFrom].getPosition();
    shiftEndPos   = getOriginalElectronOrDativePosition(&electrons[shiftingTo]);
}

void ElementObject::update(){
    int n=element->getNumberOfValenceElectrons();
    auto bondObjs=BondObject::getAllBondObjects();

    int i=0;
    for(auto &e:electrons){

        bool isInBond=false;
        for(auto bond: bondObjs){
            if(bond->contains(getOriginalElectronOrDativePosition(&e))){
                // throw std::runtime_error("fnf");
                isInBond=true;
                break;
            }
        }

        if(i<n&&!isInBond){
            e.setTransparency(1.0f);
            i++;
        }
        else{
            e.setTransparency(0.0f); 
        }
    }   

    if(i!=n){
        error->push("Element did not update properly. Please Destroy Compound Immediately");
    }

    charge.setNumber(element->getCharge());
}

Element* ElementObject::getElement(){
    return element;
}

glm::vec2 ElementObject::getPosition(){
    return position;
}

std::vector<glm::vec2> ElementObject::getElectronPositions(){

    std::vector<glm::vec2> pos;
    for(auto& e: electrons){
        pos.push_back(e.getPosition());
    }

    return pos;
}

std::vector<glm::vec2> ElementObject::getDativePositions(){

    std::vector<glm::vec2> pos;
    for(auto& dative: datives){
        pos.push_back(dative.getPosition());
    }
    return pos;
}

glm::vec2 ElementObject::getChargePosition(){
    return charge.getPosition();
    //return {position[0]+width/2,position[1]-elementTextureHeight/2};
}

glm::vec2 ElementObject::getOriginalElectronOrDativePosition(ElectronObject* electron){
    glm::vec2 pos;
    bool isInElement=false;

    for(int i=0;i<8;i++){
        if(&electrons[i]==electron){
            isInElement=true;
            if(i==0){
                pos={
                position[0]-width/2-electronDistanceDirect,position[1]-elementTextureHeight/2+electronDistanceAdjust 
                };
            }
            else if(i==1){
                pos={
                    position[0]+ width/2+electronDistanceDirect,position[1]+elementTextureHeight/2-electronDistanceAdjust 
                };         
            }
            else if(i==2){ 
                pos={
                    position[0]-width/2+electronDistanceAdjust,position[1]+elementTextureHeight/2+electronDistanceDirect 
                };         
            }
            else if(i==3){
                pos={
                    position[0]+width/2-electronDistanceAdjust,position[1]-elementTextureHeight/2-electronDistanceDirect 
                };         
            }
            else if(i==4){
                pos={
                    position[0]-width/2-electronDistanceDirect,position[1]+elementTextureHeight/2-electronDistanceAdjust 
                };
            }
            else if(i==5){
                pos={
                    position[0]+width/2-electronDistanceAdjust,position[1]+elementTextureHeight/2+electronDistanceDirect 
                };         
            }
            else if(i==6){
                pos={
                    position[0]+width/2+electronDistanceDirect,position[1]-elementTextureHeight/2+electronDistanceAdjust 
                };         
            }
            else if(i==7){
                pos={
                    position[0]-width/2+electronDistanceAdjust,position[1]-elementTextureHeight/2-electronDistanceDirect 
                };
            }
        }
    }

    for(int i=0;i<4;i++){
        if(&datives[i]==electron){
            isInElement=true;
            if(i==0){
                pos={
                    position[0]-width/2-electronDistanceDirect,position[1]
                };
            }
            else if(i==1){
                pos={
                    position[0],position[1]+elementTextureHeight/2+electronDistanceDirect
                };
            }
            else if(i==2){
                pos={
                    position[0]+width/2+electronDistanceDirect,position[1]
                };
            }
            else if(i==3){
                pos={
                    position[0],position[1]-elementTextureHeight/2-electronDistanceDirect
                };
            }   
        }
    }

    if(!isInElement){
        throw std::runtime_error("Electron is not part of element");
    }
    return pos;
}


std::vector<ElectronObject*> ElementObject::getElectronObjectsOn(glm::vec2 mousePos){
    std::vector<ElectronObject*> objs;

    for(auto& e: electrons){
        if(e.contains(mousePos)){
            objs.push_back(&e);
        }
    }

    return objs;
}

std::vector<ElectronObject*> ElementObject::getDativeObjectsOn(glm::vec2 mousePos){
    std::vector<ElectronObject*> objs;

    for(auto& e: datives){
        if(e.contains(mousePos)){
            objs.push_back(&e);
        }
    }

    return objs;
}

std::map<Element*,ElementObject*> ElementObject::getAllElementObjects(){
    return elementObjects;
}

std::array<ElectronObject*,2> ElementObject::getElectronsOfDative(ElectronObject* dative){
    return dativeToElectrons[dative];
}

ElementObject* ElementObject::getElementObjectOfElectronOrDative(ElectronObject* electron){
    return electronOrDativeToElementObject[electron];
}

