#include "callbacks.h"

bool Callbacks::isDragging = false;
glm::vec2 Callbacks::lastMouseWorldPos;

std::set<ElementObject*> Callbacks::selectedElementObjects;
std::set<ElementObject*> Callbacks::hoveredElementObjects;
bool Callbacks::isElementsDragging = false;

std::set<ElectronObject*> Callbacks::selectedElectronObjects;
std::set<ElectronObject*> Callbacks::hoveredElectronObjects;
bool Callbacks::isElectronDragging=false;

std::set<ElectronObject*> Callbacks::selectedDativeObjects;
std::set<ElectronObject*> Callbacks::hoveredDativeObjects;
bool Callbacks::isDativeDragging=false;

std::set<BondObject*> Callbacks::selectedBondObjects;
std::set<BondObject*> Callbacks::hoveredBondObjects;

int Callbacks::filterCharactersCompoundName(ImGuiInputTextCallbackData* data){
    if (strchr(disallowedCharCompoundNames, data->EventChar)){
        return 1;
    } 
    return 0;   
}

glm::vec2 Callbacks::getMouseWorldPos(double mouseX, double mouseY, Camera& cam){
    // Convert screen coordinates to Normalized Device Coordinates (NDC)
    float ndcX = (2.0f * mouseX) / cam.screenWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * mouseY) / cam.screenHeight;

    glm::vec4 clipCoords(ndcX, ndcY, 0.0f, 1.0f);

    // Inverse of projection * view matrix
    glm::mat4 invVP = glm::inverse(cam.GetVP());

    glm::vec4 worldCoords = invVP * clipCoords;

    return glm::vec2(worldCoords);
}

void Callbacks::cut(){
    std::string clipBoard;

    auto list=Render::getCompoundList();
    std::cout<<"bdb"<<std::endl;

    for(auto it: list){
        try{
    std::cout<<it->getCompoundString()<<std::endl;

            clipBoard.append(it->getCompoundString());
            Render::deleteCompound(it);
    std::cout<<it->getCompoundString()<<std::endl;
            

            clipBoard.append("\n");
        }
        catch(std::runtime_error& e){
            error->push("Compound has been corrupted");
            throw;
        }
    }
    ImGui::SetClipboardText(clipBoard.c_str());
    std::cout<<"hwuhg"<<std::endl;
}

void Callbacks::copy(){
    std::string clipBoard;
    std::cout<<"sex"<<std::endl;

    auto list=Render::getCompoundList();
    for(auto it: list){
        try{
            clipBoard.append(it->getCompoundString());
            clipBoard.append("\n");
        }
        catch(std::runtime_error& e){
            Render::deleteCompound(it);
        }
    }
    ImGui::SetClipboardText(clipBoard.c_str());
    std::cout<<"sex"<<std::endl;
}

void Callbacks::paste(){
    std::string clipBoard=std::string(ImGui::GetClipboardText());
    std::string line;

    std::istringstream stream(clipBoard);
    while (std::getline(stream, line)){
        Compound* comp;
        try{
            comp=new Compound(line);
            Render::createCompoundObject(comp); 
        }
        catch(std::invalid_argument& e){
            error->push("Compound String: "+line+ " is Invalid");
            // isError=true;
            // errorMessage="A Compound String is Invalid";
            std::cerr<<line<<" is Invalid"<<std::endl;
        }    
    }
}

void Callbacks::openContextMenu(){

    static Compound* comp=nullptr;

    ImGui::PushStyleColor(ImGuiCol_Text,contextMenuPopUpTextColor);
    ImGui::PushStyleColor(ImGuiCol_WindowBg,contextMenuPopUpBackgroundColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBg,contextMenuPopUpTitleBarColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive,contextMenuPopUpActiveTitleBarColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed,contextMenuPopUpCollapsedTitleBarColor);

    if(ImGui::BeginPopup("Context Menu")){
        if(selectedElementObjects.empty()&&selectedBondObjects.empty()){
            
        }
        else if(!selectedElementObjects.empty()&&!selectedBondObjects.empty()){
            if(ImGui::MenuItem("Delete All")){
                for(auto bond: selectedBondObjects){
                    Render::removeBond(bond);
                }
                selectedBondObjects.clear();

                for(auto el: selectedElementObjects){
                    Render::removeElement(el);
                }
                selectedElementObjects.clear();
                ImGui::CloseCurrentPopup();
            }
            //Delete All 
        }
        else if(selectedElementObjects.empty()){
            if(selectedBondObjects.size()==1){

                if(ImGui::MenuItem("Delete Bond")){
                    for(auto bond: selectedBondObjects){
                        Render::removeBond(bond);
                    }
                    selectedBondObjects.clear();
                    ImGui::CloseCurrentPopup();
                }
                //Delete Bond
            }
            else{
                if(ImGui::MenuItem("Delete Bonds")){
                    for(auto bond: selectedBondObjects){
                        Render::removeBond(bond);
                    }
                    selectedBondObjects.clear();
                    ImGui::CloseCurrentPopup();
                }
            }
            //Delete Bonds
        }
        else{
            if(selectedElementObjects.size()==1){
                if(ImGui::MenuItem("Get Element Info")){
                    ImGui::OpenPopup("Element Info");
                    ImGui::CloseCurrentPopup();
                }
                if(ImGui::MenuItem("Delete Element")){
                    for(auto el: selectedElementObjects){
                        Render::removeElement(el);
                    }
                    selectedElementObjects.clear();
                    ImGui::CloseCurrentPopup();
                }

                //Get Element Info
                //Delete Element
            }
            else{
                comp=Render::getCompoundIfExists(selectedElementObjects);
                if(comp!=nullptr){
                    if(ImGui::MenuItem("Get Molecular Mass")){
                        ImGui::OpenPopup("Compound Mass");
                        ImGui::CloseCurrentPopup();
                    }

                    if(ImGui::MenuItem("Get Molecular Formula")){
                        ImGui::OpenPopup("Compound Formula");
                        ImGui::CloseCurrentPopup();
                    }

                    if(ImGui::MenuItem("Save To File")){
                        //save to file
                        std::ofstream file;
                        bool isValidFile=true;

                        if(currentFile!="Unknown"){
                            file=std::ofstream(currentFile);
                            if (!file.is_open()){
                                error->push("Error opening file");
                                // isError=true;
                                // errorMessage="Error opening file";
                                std::cerr << "Error opening file." << std::endl;
                                isValidFile=false;
                            }
                        }
                        else{
                            nfdchar_t *outPath = NULL;
                            nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

                            if (result == NFD_OKAY){
                                if ((std::string(outPath).size()) < 4 || std::string(outPath).substr(std::string(outPath).size() - 4) != ".txt"){
                                    currentFile=outPath+std::string(".txt");
                                }
                                else{
                                    currentFile=outPath;
                                }

                                file=std::ofstream(outPath);

                                if (!file.is_open()){
                                    error->push("Error opening file");
                                    // isError=true;
                                    // errorMessage="Error opening file";
                                    std::cerr << "Error opening file." << std::endl;
                                    isValidFile=false;
                                    free(outPath);
                                }
                                    
                                free(outPath);  
                            }
                            else if (result == NFD_CANCEL){
                                error->push("User canceled");
                                // isError=true;
                                // errorMessage="User Canceled";
                                std::cerr << "User canceled\n";
                                isValidFile=false;
                            }
                            else{
                                error->push("Error Opening File Dialog");
                                // isError=true;
                                // errorMessage="Error Opening File Dialog";
                                std::cerr << "Error opening file dialog.\n";
                                isValidFile=false;
                            }
                        }
                        if(isValidFile){
                            try{
                                file<<(comp->getCompoundString()).c_str()<<std::endl;
                                ImGui::CloseCurrentPopup();
                            }
                            catch(std::runtime_error& e){
                                Render::deleteCompound(comp);
                                error->push("A Compound is Invalid");
                                std::cerr<<"A Compound is Invalid"<<std::endl;
                            }      
                        }

                        file.close();
                    }

                    if(ImGui::MenuItem("Save To App")){
                        ImGui::OpenPopup("Save To App"); 
                        ImGui::CloseCurrentPopup();
                    }

                    if(ImGui::MenuItem("Delete Compound")){
                        Render::deleteCompound(comp);
                        //save to file
                        ImGui::CloseCurrentPopup();
                    }
                    //Get Moleculor Mass
                    //Get Moleculor Formula
                    //Save to File
                    //Save to App, allowing adding name
                    //Delete Compound
                }
                else if(Render::isPartOfOneCompound(selectedElementObjects)){

                    if(ImGui::MenuItem("Select Full Compound")){
                        comp=Render::getCompoundWithElementObject(*selectedElementObjects.begin());

                        std::vector<Element*> atomList=comp->getAtoms();
                        for(auto atom: atomList){

                            if(ElementObject::getAllElementObjects()[atom]==nullptr){
                                error->push("Element was not found. Please Destroy Compound Immediately");
                                continue;
                            }

                            ElementObject::getAllElementObjects()[atom]->select(true);
                            selectedElementObjects.insert(ElementObject::getAllElementObjects()[atom]);
                        }

                        ImGui::CloseCurrentPopup();
                    }

                    if(ImGui::MenuItem("Delete Elements")){

                        for(auto el: selectedElementObjects){
                            Render::removeElement(el);
                        }

                        selectedElementObjects.clear();
                        ImGui::CloseCurrentPopup();
                    }

                    //Select Full Compound
                    //Delete Elements
                }
                else{
                    if(ImGui::MenuItem("Delete Elements")){

                        for(auto el: selectedElementObjects){
                            Render::removeElement(el);
                        }

                        selectedElementObjects.clear();
                        ImGui::CloseCurrentPopup();
                    }
                    //Delete Elements
                }
            }
        }
        ImGui::EndPopup();   
    }

    if (ImGui::BeginPopup("Element Info")) {
        ElementObject* el = *selectedElementObjects.begin();
        ImGui::Text("Symbol: %s", el->getElement()->getSymbol().c_str());
        ImGui::Text("Name: %s", el->getElement()->getName().c_str());
        ImGui::Text("Atomic Number: %d", el->getElement()->getAtomicNumber());
        ImGui::Text("Atomic Mass: %f", el->getElement()->getAtomicMass());
        ImGui::Text("Charge: %d", el->getElement()->getCharge());
        ImGui::Text("Valency: %d , %d", el->getElement()->getValency()[0], el->getElement()->getValency()[1]);

        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    if (ImGui::BeginPopup("Compound Mass")) {
        ImGui::Text("Molecular Mass: %f", comp->getMolecularMass());

        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
            comp=nullptr;
        }

        ImGui::EndPopup();
    }
    if (ImGui::BeginPopup("Compound Formula")) {
        ImGui::Text("Molecular Formula: %s", comp->getMolecularFormula().c_str());

        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
            comp=nullptr;
        }

        ImGui::EndPopup();
    }
    if(ImGui::BeginPopup("Save To App")){
        static std::vector<char> buffer(100,'\0');

        ImGui::SetKeyboardFocusHere(); 
        ImGui::Text("Enter a name for the compound:");
        ImGui::InputText("##Compound Name", buffer.data(), buffer.size(),ImGuiInputTextFlags_CallbackCharFilter,filterCharactersCompoundName);

        if(ImGui::IsKeyPressed(ImGuiKey_Enter) && strlen(buffer.data())!=0){
            addCompoundToConfigFile(std::string(buffer.data()), comp->getCompoundString());
            ImGui::CloseCurrentPopup();
            //chatgpt said might have to change
            buffer=std::vector<char>(100,'\0');
            comp=nullptr;
        }
    }

    ImGui::PopStyleColor(5);
}

void Callbacks::glfw_error_callback(int error, const char* description){
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void Callbacks::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){

    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureKeyboard)
        return;

    auto* cam=static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (!cam){
        return;
    } 
  
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if((mods & GLFW_MOD_CONTROL) && key == GLFW_KEY_C) copy();
        if((mods & GLFW_MOD_CONTROL) && key == GLFW_KEY_V) paste();
        if((mods & GLFW_MOD_CONTROL) && key == GLFW_KEY_X) cut();
 
        if (key == GLFW_KEY_LEFT) cam->Move({minCamMovement, 0});
        if (key == GLFW_KEY_RIGHT) cam->Move({-minCamMovement, 0});
        if (key == GLFW_KEY_UP) cam->Move({0, minCamMovement});
        if (key == GLFW_KEY_DOWN) cam->Move({0, -minCamMovement});
        
        if (key == GLFW_KEY_DELETE){
            for(auto bond: selectedBondObjects){
                Render::removeBond(bond);
            }
            selectedBondObjects.clear();

            for(auto el: selectedElementObjects){
                Render::removeElement(el);
            }
            selectedElementObjects.clear();
        }
        if (key == GLFW_KEY_A && (mods & GLFW_MOD_CONTROL)){
            for(auto bond: BondObject::getAllBondObjects()){
                selectedBondObjects.insert(bond);
                bond->select(true);
            }

            for(auto el: ElementObject::getAllElementObjects()){
                selectedElementObjects.insert(el.second);
                el.second->select(true);
            }
        }
    }
}

void Callbacks::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset){

    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;

    auto* cam=static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (!cam){
        return;
    }

    cam->Zoom(1+yoffset*zoomShift);
}

void Callbacks::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods){

    static double lastClickTime = 0;
    static glm::vec2 lastClickPos;
    static const double DOUBLE_CLICK_THRESHOLD = 0.25; // seconds
    static const float DOUBLE_CLICK_DISTANCE = 5.0f;   // pixels

    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;

    auto* cam=static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (!cam){
        return;
    }

    double currentTime = glfwGetTime();
    double clickDelta = currentTime - lastClickTime;

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    glm::vec2 mouseScreenPos = glm::vec2(x, y);
    glm::vec2 mouseWorldPos = getMouseWorldPos(x, y,*cam);

    bool isDoubleClick = 
    clickDelta < DOUBLE_CLICK_THRESHOLD &&
    glm::distance(mouseScreenPos, lastClickPos) < DOUBLE_CLICK_DISTANCE;

    if (action == GLFW_PRESS){
        auto elementObjs=(Render::getElementObjectsOn(mouseWorldPos));
        auto bondObjs=Render::getBondsObjectsOn(mouseWorldPos);
        auto electronObjs=Render::getElectronObjectsOn(mouseWorldPos);
        auto dativeObjs=Render::getDativeObjectsOn(mouseWorldPos);

        if(button==GLFW_MOUSE_BUTTON_RIGHT){

            for(auto it:elementObjs){
                selectedElementObjects.insert(it);
                it->select(true);
            } 

            for(auto it:bondObjs){
                selectedBondObjects.insert(it);
                it->select(true);
            }

            if(!elementObjs.empty()||!bondObjs.empty()){
                ImGui::OpenPopup("Context Menu");
            }
        }
        else if(button==GLFW_MOUSE_BUTTON_LEFT){

            if (!(mods & GLFW_MOD_SHIFT)){
                for(auto it: selectedElementObjects){
                    it->select(false);
                }
                selectedElementObjects.clear();

                for(auto it: selectedBondObjects){
                    it->select(false);
                }
                selectedBondObjects.clear();

                for(auto it: selectedElectronObjects){
                    it->select(false);
                }
                selectedElectronObjects.clear();

                for(auto it: selectedDativeObjects){
                    it->select(false);
                }
                selectedDativeObjects.clear();
            }

            if(!elementObjs.empty()){

                if(isDoubleClick){
                    bondObjs=Render::getCompoundBondObjectsWithElementObject(*elementObjs.begin());

                    for(auto it:elementObjs){
                        selectedElementObjects.insert(it);
                        it->select(true);
                    } 

                    for(auto it:bondObjs){
                        selectedBondObjects.insert(it);
                        it->select(true);
                    }
                }
                else{
                    auto it=*elementObjs.begin();

                    if (selectedElementObjects.find(it) == selectedElementObjects.end()) {
                        selectedElementObjects.insert(it);
                        it->select(true);
                    }
                } 
                isElementsDragging=true;
            }
            else if(!bondObjs.empty()){
                
                if(isDoubleClick){
                    elementObjs=Render::getCompoundElementObjectsWithBondObject(*bondObjs.begin());

                    for(auto it:elementObjs){
                        selectedElementObjects.insert(it);
                        it->select(true);
                    }

                    for(auto it:bondObjs){
                        selectedBondObjects.insert(it);
                        it->select(true);
                    }
                    isElementsDragging=true;
                }
                else{
                    auto it=*bondObjs.begin();
                    selectedBondObjects.insert(it);
                    it->select(true);
                }
            }
            else if(!electronObjs.empty()){
                for(auto it: electronObjs){
                    if(!it->isTransparent()){
                        selectedElectronObjects.insert(it);
                        it->select(true);
                        isElectronDragging=true;
                    }
                }
            }
            else if(!dativeObjs.empty()){
                auto it=*dativeObjs.begin();
                selectedDativeObjects.insert(it);
                it->select(true);              
                isDativeDragging=true;
            }
            else{
                isDragging = true;
            }
        }
    }
    else if (action == GLFW_RELEASE){
        isDragging = false;
        isElementsDragging=false;

        if(isElectronDragging){
            std::set<ElectronObject*> temp;

            for(auto it:selectedElectronObjects){
                int n=Render::checkElectronShiftingOrBonding(it);
                std::cout<<n<<std::endl;
                if(n==1||n==2||n==3){
                    // Render::resetElectronPos(it);
                    it->select(false);
                    temp.insert(it);
                }
                else if(n==0){
                    Render::resetElectronPos(it);
                }
                else if(n==-1){
                    error->push("You can not make a bond here");
                    Render::resetElectronPos(it);
                }
            }
            for(auto it: temp){
                selectedElectronObjects.erase(it);
            }
        }
        isElectronDragging=false;

        if(isDativeDragging){
            std::set<ElectronObject*> temp;

            for(auto it:selectedDativeObjects){
                int n=Render::checkDativeBonding(it);
                if(n==1){
                    // Render::resetDativePos(it);
                    it->select(false);
                    temp.insert(it);
                    selectedDativeObjects.erase(it);
                }
                else if(n==0){
                    Render::resetDativePos(it);
                }
                else if(n==-1){
                    error->push("You can not make a dative bond here");
                    Render::resetDativePos(it);
                }
            }
            for(auto it: temp){
                selectedDativeObjects.erase(it);
            }
        }
        isDativeDragging=false;
    }

    lastMouseWorldPos = mouseWorldPos;
    lastClickTime = currentTime;
    lastClickPos = mouseScreenPos;
}

void Callbacks::CursorPosCallback(GLFWwindow* window, double xpos, double ypos){

    ImGuiIO& io = ImGui::GetIO();
    
    if (io.WantCaptureMouse)
        return;

    auto* cam=static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (!cam){
        return;
    }
 
    glm::vec2 prevMouseWorldPos = lastMouseWorldPos;
    glm::vec2 mouseWorldPos = getMouseWorldPos(xpos, ypos, *cam);

    //Hover checking
    for(auto it: hoveredElementObjects){
        it->hover(false);
    }
    hoveredElementObjects = Render::getElementObjectsOn(mouseWorldPos);
    for(auto it: hoveredElementObjects){
        it->hover(true);
    }

    for(auto it: hoveredBondObjects){
        it->hover(false);
    }
    hoveredBondObjects = Render::getBondsObjectsOn(mouseWorldPos);
    for(auto it: hoveredBondObjects){
        it->hover(true);
    }

    for(auto it: hoveredElectronObjects){
        it->hover(false);
    }
    hoveredElectronObjects = Render::getElectronObjectsOn(mouseWorldPos);
    for(auto it: hoveredElectronObjects){
        if(!it->isTransparent()){
            it->hover(true);
        }
    }
    
    for(auto it: hoveredDativeObjects){
        it->hover(false);
    }
    hoveredDativeObjects = Render::getDativeObjectsOn(mouseWorldPos);
    for(auto it: hoveredDativeObjects){
        it->hover(true);
    }
    
    //Movement
    glm::vec2 delta = mouseWorldPos - lastMouseWorldPos;

    if (isElementsDragging) { 
        for(auto it: selectedElementObjects){
            it->move(delta);
            Render::moveBonds(it,delta);
        }
    }
    else if(isElectronDragging){
        for(auto it: selectedElectronObjects){
            it->move(delta);
        }
        // int n=Render::checkElectronShiftingOrBonding(it);
        // if(n==1||n==2||n==3){
        //     Render::resetElectronPos(it);
        //     it->select(false);
        //     selectedElectronObjects.erase(it);
        // }
        // else if(n==-1){
        //     error->push("You can not make a bond here");
        // }
    } 
    else if(isDativeDragging){
        for(auto it: selectedDativeObjects){
            Render::moveDative(it,delta);
        }
        //here for loop
        // int n=Render::checkDativeBonding(it);
        // if(n==1){
        //     Render::resetDativePos(it);
        //     it->select(false); 
        //     selectedDativeObjects.erase(it);
        // }
        // else if(n==-1){
        //     error->push("You can not make a dative bond here");
        // }
    }
    else if(isDragging){
        delta*=1.0f / cam->GetCurrentZoom();
        cam->Move(glm::vec2(-delta.x,-delta.y));
    }

    lastMouseWorldPos = getMouseWorldPos(xpos, ypos, *cam);
}

void Callbacks::FrameSizeCallback(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);

    auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window)); 
    if (cam) {
        cam->Resize((float)width, (float)height);
    }

    ImGuiIO& io=ImGui::GetIO();
    io.DisplaySize=ImVec2((float)width, (float)height);
} 