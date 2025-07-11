#include "render.h"

void Render::Render(){

    //Elements and their electrons
    for(auto compound:compoundList){
        std::vector<Element*> atomList=compound->getAtoms();
        for(auto atom: atomList){
            if(ElementObject::elementObjects[atom]==nullptr){
                error->Push("Element was not rendered. Please Destroy Compound Immediately");
                
                continue;
            }
            ElementObject::elementObjects[atom]->Render();
        }
    }

    //Bonds
    for(auto it:BondObject::bonds){
        it->Render();
    }
}

void Render::createCompoundObject(Compound* compound){

    if (!compound || compound->getAtoms().empty()){
        error->Push("Invalid or empty compound in createElementObjectsFromCompound()");
        return;
    }

    ImGuiIO& io = ImGui::GetIO();

    std::set<Element*> visited;
    std::unordered_map<Element*, glm::vec2> positions;

    // Step 1: Layout atoms relative to (0,0)
    glm::vec2 origin = glm::vec2(0.0f);
    float spacing = elementTextureHeight * elementSpacingAmount;

    std::vector<glm::vec2> directions = {
        {1, 0},   // right
        {0, 1},   // up
        {-1, 0},  // left
        {0, -1}   // down
    };

    std::queue<std::pair<Element*, glm::vec2>> q;
    Element* root = compound->getAtoms()[0];
    q.push({root, origin});
    positions[root] = origin;

    while (!q.empty()) {
        auto [current, pos] = q.front();
        q.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        const auto& bondMap = compound->getBonds();
        auto it = bondMap.find(current);
        const auto& neighbors = it->second;
        int dirIndex = 0;

        for (const auto& [neighbor, bondType] : neighbors) {
            if (visited.count(neighbor)) continue;

            glm::vec2 offset = directions[dirIndex % directions.size()] * spacing;
            glm::vec2 neighborPos = pos + offset;

            if (positions.count(neighbor) == 0) {
                positions[neighbor] = neighborPos;
                q.push({neighbor, neighborPos});
            }

            dirIndex++;
        }
    }

    // Step 2: Compute bounding box of all positions
    glm::vec2 minPos = positions.begin()->second;
    glm::vec2 maxPos = positions.begin()->second;

    for (const auto& [el, pos] : positions) {
    minPos.x = std::min(minPos.x, pos.x);
    minPos.y = std::min(minPos.y, pos.y);
    maxPos.x = std::max(maxPos.x, pos.x);
    maxPos.y = std::max(maxPos.y, pos.y);
    }

    glm::vec2 compoundCenter = (minPos + maxPos) * 0.5f;
    //glm::vec2 screenCenter = camera->GetCurrentPosition();
    glm::vec2 screenCenter = camera->GetCurrentPosition() + glm::vec2(io.DisplaySize.x*(1-sideMenuWidthPerCentCopy), io.DisplaySize.y) * 0.5f / camera->zoom;
    glm::vec2 shift = screenCenter - compoundCenter;

    // Step 3: Create ElementObjects with shifted positions
    for (const auto& [el, pos] : positions) {
        glm::vec2 finalPos = pos + shift;
        try {
            auto* obj = new ElementObject(finalPos, el);
            ElementObject::elementObjects[el] = obj;
        } catch (const std::exception& e) {
            error->Push("Failed to create ElementObject: " + std::string(e.what()));
        }

    }
        auto bonds = compound->getBonds();

    for (auto& [el1, bondedList] : bonds) {
        ElementObject* obj1 = ElementObject::elementObjects[el1];
        if (!obj1) continue;

        for (auto& [el2, bondType] : bondedList) {
            if (el1 > el2) continue; // Prevent double rendering

            ElementObject* obj2 = ElementObject::elementObjects[el2];
            if (!obj2) continue;

            glm::vec2 bestA, bestB;
            float minDist = std::numeric_limits<float>::max();

            std::vector<glm::vec2> spots1, spots2;

            switch (bondType) {
                case 0: // Covalent
                    spots1 = obj1->getElectronPositions();
                    spots2 = obj2->getElectronPositions();
                    break;
                case 1: case -1: // Ionic
                    spots1 = { obj1->getChargePosition() };
                    spots2 = { obj2->getChargePosition() };
                    break;
                case 2: case -2: // Dative
                    spots1 = obj1->getDativePositions();
                    spots2 = obj2->getDativePositions();
                    break;
                default:
                    error->Push("Unknown bond type in compound");
                    continue;
            }

            for (const auto& p1 : spots1) {
                for (const auto& p2 : spots2) {
                    float dist = glm::distance(p1, p2);
                    if (dist < minDist) {
                        minDist = dist;
                        bestA = p1;
                        bestB = p2;
                    }
                }
            }

            // Determine donor based on bondType
            std::vector<glm::vec2> finalEnds;
            std::vector<ElementObject*> elements;
            if (bondType == 1 || bondType == -2) {
                finalEnds = { bestB, bestA }; // el2 gives to el1
                elements={obj2,obj1};
            } else {
                finalEnds = { bestA, bestB }; // el1 gives to el2
                elements={obj1,obj2};

            }

            try {
                new BondObject(finalEnds, elements, std::abs(bondType));
            } catch (const std::exception& e) {
                error->Push("Failed to create BondObject: " + std::string(e.what()));
            }
        }
    }

    Render::compoundList.push_back(compound);

}

ElementObject* Render::getElementClicked(glm::vec2 mousePos){
    for (auto& el : ElementObject::elementObjects) {
        // if (mousePos.x >= el.second->position.x && mousePos.x <= el.second->position.x + el.second->width&&
        //     mousePos.y >= el.second->position.y && mousePos.y <= el.second->position.y + elementTextureHeight) {
        //     return el.second;
        // }
        float halfWidth = el.second->width / 2.0f;
float halfHeight = elementTextureHeight / 2.0f;
glm::vec2 pos = el.second->position;

if (mousePos.x >= pos.x - halfWidth && mousePos.x <= pos.x + halfWidth &&
    mousePos.y >= pos.y - halfHeight && mousePos.y <= pos.y + halfHeight)
{
    return el.second;
}
    }
    return nullptr;
} 

void Render::MoveBonds(ElementObject* el,glm::vec2 delta){
    for (auto& bond: BondObject::bonds){
        if (bond->elements[0]==el){
            bond->Move(delta,0);
        }

        if (bond->elements[1]==el){
            bond->Move(delta,1);
        }
    }
}

