#include "UIGeneration.h"

void UI::TopMenu(){

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    static bool showBackgroundColor=false;
    static bool showTopMenuColor=false;
    static bool showTopMenuTextColor=false;
    static bool showElementColor=false;
    static bool showElementTextColor=false;
    static bool showElementBoxColor=false;
    static bool showCompoundColor=false;
    static bool showCompoundTextColor=false;
    static bool showCompoundBoxColor=false;
    static bool showScrollColor=false;
    static bool showSearchColor=false;

    static bool showInsertDirect=false;
    static bool showInsertFile=false;

    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, topMenuButtonColor);      
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, topMenuHoveredButtonColor);
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, topMenuActiveButtonColor); 

    ImGui::PushStyleColor(ImGuiCol_Button, topMenuButtonColor);      
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, topMenuHoveredButtonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, topMenuActiveButtonColor);   

    ImGui::PushStyleColor(ImGuiCol_Text, topMenuTextColor);  

    if(ImGui::BeginMainMenuBar()){

        if(ImGui::BeginMenu("Settings")){
            if (ImGui::MenuItem("Background Color")){
                showBackgroundColor=!showBackgroundColor;
            }
            if (ImGui::MenuItem("Top Menu Color")){
                showTopMenuColor=!showTopMenuColor;
            }
            if (ImGui::MenuItem("Top Menu Text Color")){
                showTopMenuTextColor=!showTopMenuTextColor;
            }
            if (ImGui::MenuItem("Element Tab Color")){
                showElementColor=!showElementColor;
            }
            if (ImGui::MenuItem("Element Text Color")){
                showElementTextColor=!showElementTextColor;
            }
            if (ImGui::MenuItem("Element Box Color")){
                showElementBoxColor=!showElementBoxColor;
            }
            if (ImGui::MenuItem("Compound Tab Color")){
                showCompoundColor=!showCompoundColor;
            }
            if (ImGui::MenuItem("Compound Text Color")){
                showCompoundTextColor=!showCompoundTextColor;
            }
            if (ImGui::MenuItem("Compound Box Color")){
                showCompoundBoxColor=!showCompoundBoxColor;
            }
            if (ImGui::MenuItem("Scroll Bar Color")){
                showScrollColor=!showScrollColor;
            }
            if (ImGui::MenuItem("Search Bar Color")){
                showSearchColor=!showSearchColor;
            }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Edit")){

            // if (ImGui::MenuItem("Undo", "CTRL+Z")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_Z))){

            // }
            // if (ImGui::MenuItem("Redo", "CTRL+Y")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_Y))){
                
            // }

            ImGui::Separator(); 
            
            if (ImGui::MenuItem("Cut", "CTRL+X")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_X))){
                Cut();
            }
            if (ImGui::MenuItem("Copy", "CTRL+C")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_C))){
                Copy();
            }
            if (ImGui::MenuItem("Paste", "CTRL+V")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_V))){ 
                Paste();
            }
            if(ImGui::MenuItem("Hydrogen Filler")){
                auto list=Render::compoundList;
                for(auto it: list){
                    try{
                        if((it->hydrogenFiller())==0){
                            throw std::runtime_error("Hydrogen Bond could not form");
                        }
                    }
                    catch(std::runtime_error& e){
                        // isError=true;
                        // errorMessage=e.what();
                        error->Push("A compound was corrupt. It will be destroyed");
                        std::cerr<<"A compound was corrupt"<<std::endl;
                        for(auto atom: it->getAtoms()){
                            free(atom);
                        }
                        free(it);
                    }

                }
                //Render::ReRenderCompounds();
            }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Insert")){
            if (ImGui::MenuItem("Direct")) {
                showInsertDirect=!showInsertDirect;
            }
            if (ImGui::MenuItem("From File")) {
                showInsertFile=!showInsertDirect;
            }
            ImGui::EndMenu();
        }

        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX()+topMenu_____Padding);

        ImGui::PushStyleColor(ImGuiCol_Text,openFilePopUpTextColor);
        ImGui::PushStyleColor(ImGuiCol_WindowBg,openFilePopUpBackgroundColor);
        ImGui::PushStyleColor(ImGuiCol_TitleBg,openFilePopUpTitleBarColor);
        ImGui::PushStyleColor(ImGuiCol_TitleBgActive,openFilePopUpActiveTitleBarColor);
        ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed,openFilePopUpCollapsedTitleBarColor);

        if(ImGui::Button("Open")){
            bool openFile=false;

            ImGui::OpenPopup("Progress Loss Warning");
            if(ImGui::BeginPopupModal("Progress Loss Warning",nullptr,ImGuiWindowFlags_AlwaysAutoResize)){
                ImGui::Text("Warning: You will lose unsaved progress");
                ImGui::Text("Do you Wish to Continue?");
                
                if(ImGui::Button("Cancel")){
                    openFile=false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if(ImGui::Button("Ok",ImVec2(ImGui::GetCursorPos().x,ImGui::GetWindowSize().y-80))){
                    openFile=true;
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::EndPopup();
            if(openFile){
                open();
            }
        }        

        ImGui::PopStyleColor(5);

        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX()+topMenu_____Padding);
        if(ImGui::Button("Save")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_S))){
            if(currentFile=="Unknown"){
                saveAs();
            }        
            else{
                save();
            }
        }         

        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX()+topMenu_____Padding);
        if(ImGui::Button("Save As")||(ImGui::IsKeyDown(ImGuiMod_Ctrl)&& (ImGui::IsKeyPressed(ImGuiKey_LeftShift)||ImGui::IsKeyPressed(ImGuiKey_RightShift)) && ImGui::IsKeyPressed(ImGuiKey_S))){
            saveAs();
        }            

        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX()+topMenu_____Padding);
        if(ImGui::Button("Help")){
            openHelpLink();
        }

        ImGui::PushStyleColor(ImGuiCol_Text,fileNameColor);
        ImGui::SameLine();
        ImGui::SetCursorPosX(io.DisplaySize.x-topMenu_____Padding-ImGui::CalcTextSize((std::string("Current File: ")+currentFile).c_str()).x);
        ImGui::Text("%s",(std::string("Current File: ")+currentFile).c_str());

        ImGui::PopStyleColor();
        ImGui::EndMainMenuBar();
    }

    ImGui::PushStyleColor(ImGuiCol_Text,settingsColorPickersTextColor);
    ImGui::PushStyleColor(ImGuiCol_WindowBg,settingsColorPickersBackgroundColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBg,settingsColorPickersTitleBarColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive,settingsColorPickersActiveTitleBarColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed,settingsColorPickersCollapsedTitleBarColor);

    if(showBackgroundColor){
        ImGui::Begin("Background Color Picker", &showBackgroundColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Background Color", (float*)&windowColor);
        changeCustomJSON("windowColor",windowColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("windowColor",windowColor);
        }
        ImGui::End();
    }
    if(showTopMenuColor){
        ImGui::Begin("Top Menu Color Picker", &showTopMenuColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Top Menu Color", (float*)&topMenuButtonColor); 
        changeCustomJSON("topMenuButtonColor",topMenuButtonColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("topMenuButtonColor",topMenuButtonColor);
        }
        ImGui::End();
    }
    if(showTopMenuTextColor){
        ImGui::Begin("Top Menu Text Color Picker", &showTopMenuTextColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Top Menu Text Color", (float*)&topMenuTextColor); 
        changeCustomJSON("topMenuTextColor",topMenuTextColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("topMenuTextColor",topMenuTextColor);
        }
        ImGui::End();
    }
    if(showElementColor){
        ImGui::Begin("Element Tab Color Picker", &showElementColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Element Tab Color", (float*)&elementWindowColor); 
        changeCustomJSON("elementWindowColor",elementWindowColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("elementWindowColor",elementWindowColor);
        }
        ImGui::End();
    }
    if(showElementTextColor){
        ImGui::Begin("Element Text Color Picker", &showElementTextColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Element Text Color", (float*)&elementWindowTextColor); 
        changeCustomJSON("elementWindowTextColor",elementWindowTextColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("elementWindowTextColor",elementWindowTextColor);
        }
        ImGui::End();
    }
    if(showElementBoxColor){
        ImGui::Begin("Element Box Color Picker", &showElementBoxColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Element Box Color", (float*)&elementButtonColor); 
        changeCustomJSON("elementButtonColor",elementButtonColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("elementButtonColor",elementButtonColor);
        }
        ImGui::End();
    }
    if(showCompoundColor){
        ImGui::Begin("Compound Tab Color Picker", &showCompoundColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Compound Tab Colorr", (float*)&compoundWindowColor); 
        changeCustomJSON("compoundWindowColor",compoundWindowColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("compoundWindowColor",compoundWindowColor);
        }
        ImGui::End();
    }
    if(showCompoundTextColor){
        ImGui::Begin("Compound Text Color Picker", &showCompoundTextColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Compound Text Color", (float*)&compoundWindowTextColor); 
        changeCustomJSON("compoundWindowTextColor",compoundWindowTextColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("compoundWindowTextColor",compoundWindowTextColor);
        }
        ImGui::End();
    }
    if(showCompoundBoxColor){
        ImGui::Begin("Compound Box Color Picker", &showCompoundBoxColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Compound Box Color", (float*)&compoundWindowColor); 
        changeCustomJSON("compoundWindowColor",compoundWindowColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("compoundWindowColor",compoundWindowColor);
        }
        ImGui::End();
    }
    if(showScrollColor){
        ImGui::Begin("Scroll Bar Color Picker", &showScrollColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Scroll Bar Color", (float*)&scrollBarColor); 
        changeCustomJSON("scrollBarColor",scrollBarColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("scrollBarColor",scrollBarColor);
        }
        ImGui::End();
    }
    if(showSearchColor){
        ImGui::Begin("Search Bar Color Picker", &showSearchColor,ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorEdit4("##Search Bar Color", (float*)&searchBarColor); 
        changeCustomJSON("searchBarColor",searchBarColor);
        if(ImGui::Button("Reset to Default")){
            restoreToDefault("searchBarColor",searchBarColor);
        }
        ImGui::End();
    }

    ImGui::PopStyleColor(5);

    ImGui::PushStyleColor(ImGuiCol_FrameBg, insertDirectColor);  
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, insertDirectHoveredColor);  
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, insertDirectTypingColor);  

    ImGui::PushStyleColor(ImGuiCol_Text, insertDirectTextColor);  
    
    if(showInsertDirect){
        std::string compoundString;

        static char buffer[1000]="";
        
        ImGui::InputTextWithHint("Compound String", "Enter Compound String", buffer, sizeof(char),ImGuiInputTextFlags_CallbackCharFilter, FilterLettersCompoundString);
        compoundString=std::string(buffer);
        std::transform(compoundString.begin(),compoundString.end(),compoundString.begin(),::tolower);

        if(*(compoundString.end()-1)=='\n'){
            Compound* comp;
            try{
                comp=new Compound(compoundString);
                Render::createCompoundObject(comp); 
            }
            catch(std::invalid_argument& e){
                error->Push(compoundString+" is Invalid");
                // error>>
                // isError=true;
                // errorMessage=e.what();
                std::cerr<<compoundString<<" is Invalid"<<std::endl;
            }   

            showInsertDirect=!showInsertDirect;
        }
    }
    if(showInsertFile){
        nfdchar_t *outPath = NULL;
        nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

            if (result == NFD_OKAY && std::string(outPath).size() < 4 && (std::string(outPath).substr(std::string(outPath).size() - 4) != ".txt")){
                std::ifstream file(outPath);
                if (!file.is_open())
                {
                    // isError=true;
                    // errorMessage="Error opening file";

                    error->Push("Error opening file");
                    std::cerr << "Error opening file" << std::endl;
                    free(outPath);

                }
                
                std::string line;
                while (std::getline(file, line))
                {
                    Compound * comp;
                    try{
                        comp=new Compound(line);
                        Render::createCompoundObject(comp); 
                    }
                    catch(std::invalid_argument& e){
                        // isError=true;
                        // errorMessage=e.what();
                        error->Push("Compound String: "+line+ " is Invalid");
                        // isError=true;
                        // errorMessage="A Compound String is Invalid";
                        std::cerr<<line<<" is Invalid"<<std::endl;
                    }   
                }

                file.close();
                free(outPath);  
        
        }
        else if (result == NFD_CANCEL){
            error->Push("User canceled");
            // isError=true;
            // errorMessage="User Canceled";
            std::cerr << "User canceled\n";
        }
        else{
            error->Push("Error Opening File Dialog");
            // isError=true;
            // errorMessage="Error Opening File Dialog";
            std::cerr << "Error opening file dialog.\n";
        }
        showInsertFile=!showInsertFile;
    }

    ImGui::PopStyleColor(4);

    ImGui::PopStyleColor(7);
}

void UI::Cut(){
    std::string clipBoard;

    auto list=Render::compoundList;
    for(auto it: list){
        try{
            clipBoard.append(it->getCompoundString());
            for(auto atom: it->getAtoms()){
                free(atom);
            }
            free(it);
            clipBoard.append("\n");
        }
        catch(std::runtime_error& e){
            for(auto atom: it->getAtoms()){
                free(atom);
            }
            free(it);
            error->Push("A Compound is Invalid");
            // isError=true;
            // errorMessage="A Compound is Invalid";
            std::cerr<<"A Compound is Invalid"<<std::endl;
        }
    }
    ImGui::SetClipboardText(clipBoard.c_str());
}

void UI::Copy(){
    std::string clipBoard;

    auto list=Render::compoundList;
    for(auto it: list){
        try{
            clipBoard.append(it->getCompoundString());
            clipBoard.append("\n");
        }
        catch(std::runtime_error& e){
            for(auto atom: it->getAtoms()){
                free(atom);
            }
            free(it);
            error->Push("Compound is Invalid");
            // isError=true;
            // errorMessage="A Compound is Invalid";
            std::cerr<<"Compound is Invalid"<<std::endl;
        }
    }
    ImGui::SetClipboardText(clipBoard.c_str());
}

void UI::Paste(){
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
            error->Push("Compound String: "+line+ " is Invalid");
            // isError=true;
            // errorMessage="A Compound String is Invalid";
            std::cerr<<line<<" is Invalid"<<std::endl;
        }    
    }
}



int UI::FilterLettersCompoundString(ImGuiInputTextCallbackData* data){
    if (strchr(disallowedCharCompoundString, data->EventChar)||isalpha(data->EventChar)){
        return 1;
    } 
    return 0;   
}

void UI::openHelpLink() {
    #ifdef _WIN32
        ShellExecute(0, 0, helpLink, 0, 0, SW_SHOWNORMAL);  // Windows
    #elif __APPLE__
        std::string command = "open " + std::string(helpLink);  // macOS
        system(command.c_str());
    #else
        std::string command = "xdg-open " + std::string(helpLink);  // Linux
        system(command.c_str());
    #endif
}

void UI::saveAs(){ 
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

    if (result == NFD_OKAY){
        if ((std::string(outPath).size()) < 4 || std::string(outPath).substr(std::string(outPath).size() - 4) != ".txt"){
            currentFile=outPath+std::string(".txt");
        }
        else{
            currentFile=outPath;
        }

        std::ofstream file(outPath);

        if (!file.is_open()){
            error->Push("Error opening file");
            // isError=true;
            // errorMessage="Error opening file";
            std::cerr << "Error opening file." << std::endl;
            free(outPath);
            return;
        }
        
        auto list=Render::compoundList;
        for(auto it: list){
            try{
                file<<(it->getCompoundString()).c_str()<<std::endl;
            }
            catch(std::runtime_error& e){
                for(auto atom: it->getAtoms()){
                    free(atom);
                }
                free(it);
                // isError=true;
                // errorMessage="A Compound is Invalid";
                error->Push("A Compound is Invalid");
                std::cerr<<"A Compound is Invalid"<<std::endl;
            }
            
        }
            
        file.close();
        free(outPath);  
    }
    else if (result == NFD_CANCEL){
        error->Push("User canceled");
        // isError=true;
        // errorMessage="User Canceled";
        std::cerr << "User canceled\n";
    }
    else{
        error->Push("Error Opening File Dialog");
        // isError=true;
        // errorMessage="Error Opening File Dialog";
        std::cerr << "Error opening file dialog.\n";
    }
}

void UI::save(){

    std::ofstream file(currentFile);
    if (!file.is_open()){
        error->Push("Error opening file");
        // isError=true;
        // errorMessage="Error opening file";
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    std::string line;
    auto list=Compound::getListOfCompounds();
    for(auto it: list){
        try{
            file<<(it->getCompoundString()).c_str()<<std::endl;
        }
        catch(std::runtime_error& e){
            for(auto atom: it->getAtoms()){
                free(atom);
            }
            free(it);
            error->Push("A Compound is Invalid");
            std::cerr<<"A Compound is Invalid"<<std::endl;
        }
    }

    file.close();
}

void UI::open(){
    
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

    if (result == NFD_OKAY && std::string(outPath).size() < 4 && (std::string(outPath).substr(std::string(outPath).size() - 4) != ".txt")){
        std::ifstream file(outPath);
        if (!file.is_open()){
            error->Push("Error opening file");
            // isError=true;
            // errorMessage="Error opening file";
            std::cerr << "Error opening file." << std::endl;
            free(outPath);
            return;
        }
        
        std::string line;
        auto list=Render::compoundList;
        for(auto it: list){
            for(auto atom: it->getAtoms()){
                free(atom);
            }
            free(it);
        }
        Render::compoundList.clear();

        while (std::getline(file, line)){
            Compound* comp;
            try{
                comp=new Compound(line);
                Render::createCompoundObject(comp); 
            }
            catch(std::invalid_argument& e){
                error->Push("Compound String: "+line+ " is Invalid");
                // isError=true;
                // errorMessage="A Compound String is Invalid";
                std::cerr<<line<<" is Invalid"<<std::endl;
            }    
        }
        currentFile=outPath;

        file.close();
        free(outPath);
    }
    else if (result == NFD_CANCEL){
        error->Push("User canceled");
        // isError=true;
        // errorMessage="User Canceled";
        std::cerr << "User canceled\n";
    }
    else{
        error->Push("Error Opening File Dialog");
        // isError=true;
        // errorMessage="Error Opening File Dialog";
        std::cerr << "Error opening file dialog.\n";
    }

}


