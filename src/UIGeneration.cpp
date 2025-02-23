#include "UIGeneration.h"

void UI::SideMenu(ImFont* searchFontSmall, ImFont* searchFontLarge,ImFont* childWindowFontSmall, ImFont* childWindowFontLarge,ImFont* numberFont,ImFont* symbolFont,ImFont* nameFont,ImFont* massFont,ImFont* compoundNameFont,ImFont* molecularFormulaFont){
    
    static ImVec2 prevWindowSize=ImVec2(0,0);
    static double sideMenuWidthPerCent=initialSideMenuWidthPerCent;

    static std::vector<std::string> currentSearchArray={};

    ImGuiIO& io=ImGui::GetIO(); (void)io;
    
    ImGui::PushStyleColor(ImGuiCol_WindowBg, sideMenuColor);

    if(ImGui::GetFrameCount()==0||prevWindowSize.x != io.DisplaySize.x ||prevWindowSize.y != io.DisplaySize.y){
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - sideMenuWidthPerCent*io.DisplaySize.x, 0));
        ImGui::SetNextWindowSize(ImVec2(sideMenuWidthPerCent*io.DisplaySize.x, io.DisplaySize.y)); 
        ImGui::SetNextWindowBgAlpha(1.0f);
    }
    ImGui::SetNextWindowSizeConstraints(ImVec2(minimumSideMenuWidth, io.DisplaySize.y), ImVec2(int(io.DisplaySize.x/2), io.DisplaySize.y));

    // Begin window with no resizing, moving, or collapsing
    ImGuiWindowFlags window_flags =  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus;

    if (ImGui::Begin("Side Menu", nullptr, window_flags)){

        //Element and Compound Tabs
        ElementAndCompoundMenu(childWindowFontSmall,childWindowFontLarge,numberFont, symbolFont, nameFont,massFont, compoundNameFont,molecularFormulaFont,currentSearchArray);

        //why the fuck is the app breaking when i put searchbar first
        SearchBar(searchFontSmall,searchFontLarge,currentSearchArray);


        sideMenuWidthPerCent=ImGui::GetWindowSize().x/io.DisplaySize.x;
    }

    ImGui::End();

    ImGui::PopStyleColor(1);

    prevWindowSize=io.DisplaySize;
}

void UI::ElementAndCompoundMenu(ImFont* childWindowFontSmall, ImFont* childWindowFontLarge,ImFont* numberFont,ImFont* symbolFont,ImFont* nameFont,ImFont* massFont,ImFont* compoundNameFont,ImFont* molecularFormulaFont,const std::vector<std::string>& currentSearchArray){

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    static ImVec2 prevSideMenuSize=ImVec2(0,0);
    
    //You Can't Change Static
    static double elementHeightPerCent=initialElementHeightPerCent;
    static int elementHeight=elementHeightPerCent*io.DisplaySize.y;

    static double compoundHeightPerCent=1-elementHeightPerCent-initialSearchBarHeightPerCent-scrollerHeightPerCent;
    static int compoundHeight=compoundHeightPerCent*io.DisplaySize.y;

    if( prevSideMenuSize.y != io.DisplaySize.y){
        elementHeight=elementHeightPerCent*io.DisplaySize.y;
        compoundHeight=compoundHeightPerCent*io.DisplaySize.y;
    }

    ImGui::PushStyleColor(ImGuiCol_ChildBg,  elementWindowColor);  
    ImGui::PushStyleColor(ImGuiCol_Border,elementWindowBorderColor);  
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, elementWindowBorderShadowColor);  

    if(io.DisplaySize.y>largeWindowHeight){
        ImGui::PushFont(childWindowFontLarge);
    }
    else{
        ImGui::PushFont(childWindowFontSmall);
    }

    ImGui::PushStyleColor(ImGuiCol_Text, elementWindowTextColor);

    double sizeChange=ImGui::GetWindowSize().x-prevSideMenuSize.x;
    if(ImGui::BeginChild(elementTitle, ImVec2(ImGui::GetWindowSize().x-elementCompound_____Padding, elementHeight), false)){

        //for topmenu
        ImGui::Text(" ");

        ImVec2 textSize = ImGui::CalcTextSize(elementTitle);
        float windowWidth = ImGui::GetWindowSize().x;
        float textPosX = (windowWidth - textSize.x) * 0.5f; 
        ImGui::SetCursorPosX(textPosX);
        ImGui::Text("%s",elementTitle);
        
        bool isFirstBox=true;
        for (auto i: initialElements){
            std::string lowerName=names[i-1];
            std::transform(lowerName.begin(),lowerName.end(),lowerName.begin(),::tolower);

            std::string lowerSymbol=symbols[i-1];
            std::transform(lowerSymbol.begin(),lowerSymbol.end(),lowerSymbol.begin(),::tolower);

            if(std::find(currentSearchArray.begin(),currentSearchArray.end(),lowerName)!=currentSearchArray.end()||std::find(currentSearchArray.begin(),currentSearchArray.end(),lowerSymbol)!=currentSearchArray.end()){
                GenerateElementButton(i,sizeChange,numberFont, symbolFont, nameFont, massFont,isFirstBox);
                isFirstBox=false;
            }   
        }

        for(int i=1;i<=118;i++){
            std::string lowerName=names[i-1];
            std::transform(lowerName.begin(),lowerName.end(),lowerName.begin(),::tolower);

            std::string lowerSymbol=symbols[i-1];
            std::transform(lowerSymbol.begin(),lowerSymbol.end(),lowerSymbol.begin(),::tolower);

            if(std::find(initialElements.begin(),initialElements.end(),i)==initialElements.end()&& (std::find(currentSearchArray.begin(),currentSearchArray.end(),lowerName)!=currentSearchArray.end()||std::find(currentSearchArray.begin(),currentSearchArray.end(),lowerSymbol)!=currentSearchArray.end())){
                GenerateElementButton(i,sizeChange, numberFont, symbolFont, nameFont, massFont,isFirstBox);
                isFirstBox=false;
            }
        }   
    }

    ImGui::EndChild();
    
    ImGui::PopStyleColor(4);
    ImGui::PopFont();

    ImGui::InvisibleButton("##splitter", ImVec2(ImGui::GetWindowSize().x, scrollerHeightPerCent*io.DisplaySize.y));

    if(ImGui::IsItemActive()){
        if(elementHeight<io.DisplaySize.y*minimumWindowPerCent){
            elementHeight+=offset;
            compoundHeight-=offset;
        }
        else if(compoundHeight<io.DisplaySize.y*minimumWindowPerCent){
            compoundHeight+=offset;
            elementHeight-=offset;
        }
        else{
            elementHeight+=io.MouseDelta.y;
            compoundHeight-=io.MouseDelta.y;
        }
    }

        //idk why 15.0f
    ImGui::GetWindowDrawList()->AddRectFilled(
        ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y),
        ImVec2(ImGui::GetItemRectMax().x-elementCompound_____Padding, ImGui::GetItemRectMax().y),
        scrollBarColor,15.0f, ImDrawFlags_RoundCornersAll
    );

    ImGui::PushStyleColor(ImGuiCol_ChildBg,  compoundWindowColor);  
    ImGui::PushStyleColor(ImGuiCol_Border,compoundWindowBorderColor);  
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, compoundWindowBorderShadowColor);  

    if(io.DisplaySize.y>largeWindowHeight){
        ImGui::PushFont(childWindowFontLarge);
    }
    else{
        ImGui::PushFont(childWindowFontSmall);
    }

    ImGui::PushStyleColor(ImGuiCol_Text, compoundWindowTextColor);

    //idk why -70 figure it out later idk why its -15 now
    if(ImGui::BeginChild(compoundTitle, ImVec2(ImGui::GetWindowSize().x-elementCompound_____Padding,compoundHeight-IDKWhyOffset), false)){
        
        ImVec2 textSize = ImGui::CalcTextSize(compoundTitle);
        float windowWidth = ImGui::GetWindowSize().x;
        float textPosX = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(textPosX);
        ImGui::Text("%s",compoundTitle);

        bool isFirstBox=true;
        for(int i=1;i<=compoundNumbers.size();i++){
            if(std::find(currentSearchArray.begin(),currentSearchArray.end(),compoundNumbers[i-1])!=currentSearchArray.end()){
                GenerateCompoundButton(i,sizeChange,compoundNameFont,molecularFormulaFont,isFirstBox);
                isFirstBox=false;
            }
        }
    }

    ImGui::EndChild();
    
    ImGui::PopStyleColor(4);
    ImGui::PopFont();

    elementHeightPerCent=elementHeight/io.DisplaySize.y;
    compoundHeightPerCent=compoundHeight/io.DisplaySize.y;

    prevSideMenuSize=ImGui::GetWindowSize();
}

void UI::GenerateElementButton(int atomicNumber, double sizeChange,ImFont* numberFont,ImFont* symbolFont,ImFont* nameFont,ImFont* massFont, bool isFirstBox){

    static int customElementAtomicNumber=1;
    static bool showCustomElementPopUp=false;

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    
    //Keep screenpos
    static ImVec2 initialButtonCorner = ImGui::GetCursorScreenPos();
    static ImVec2 buttonCorner = ImGui::GetCursorScreenPos();

    //its gettong strecthe and stuff
    //holy shit im dumb
    if(sizeChange && isFirstBox){
        initialButtonCorner.x=ImGui::GetCursorScreenPos().x;
        buttonCorner.x=ImGui::GetCursorScreenPos().x;
    }

    float remainingSpace=io.DisplaySize.x-buttonCorner.x-elementButtonSize.x;
    if(remainingSpace>elementButtonSize.x && !isFirstBox){
        ImGui::SetCursorScreenPos(ImVec2(buttonCorner.x+elementButtonSize.x,buttonCorner.y));
    }
    else if(!isFirstBox){
        ImGui::SetCursorScreenPos(ImVec2(initialButtonCorner.x,buttonCorner.y+elementButtonSize.y));
    }

    buttonCorner = ImGui::GetCursorScreenPos();

    draw_list->AddRectFilled(
        buttonCorner,
        ImVec2(buttonCorner.x + elementButtonSize.x, buttonCorner.y + elementButtonSize.y),
        elementButtonColor,
        elementButtonCurve
    );
    
    ImGui::InvisibleButton(std::to_string(atomicNumber).c_str(), elementButtonSize);

    if (ImGui::IsItemHovered()) {
        draw_list->AddRectFilled(
            buttonCorner,
            ImVec2(buttonCorner.x + elementButtonSize.x, buttonCorner.y + elementButtonSize.y),
            elementButtonHoveredColor,
            elementButtonCurve
        ); 
    }
    if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
        
        draw_list->AddRectFilled(
            buttonCorner,
            ImVec2(buttonCorner.x + elementButtonSize.x, buttonCorner.y + elementButtonSize.y),
            elementButtonClickedColor,
            elementButtonCurve
        );  
        CompoundObject* obj=new CompoundObject(atomicNumber);
    }
    if(ImGui::IsItemClicked(ImGuiMouseButton_Right)){
        draw_list->AddRectFilled(
            buttonCorner,
            ImVec2(buttonCorner.x + elementButtonSize.x, buttonCorner.y + elementButtonSize.y),
            elementButtonClickedColor,
            elementButtonCurve
        );  
        customElementAtomicNumber=atomicNumber;
        showCustomElementPopUp=true;
    }

    draw_list->AddRect(buttonCorner,
        ImVec2(buttonCorner.x + elementButtonSize.x, buttonCorner.y + elementButtonSize.y), elementButtonBorderColor, elementButtonCurve,
        0, 
        elementButtonBorderThickness
    );
    
    ImGui::PushFont(numberFont);
    draw_list->AddText(
        ImVec2(ImGui::GetItemRectMin().x+elementButtonBorderThickness,ImGui::GetItemRectMin().y+elementButtonBorderThickness),
        atomicNumberColor,
        std::to_string(atomicNumber).c_str()
    );
    ImGui::PopFont();

    ImGui::PushFont(symbolFont);
    draw_list->AddText(
        ImVec2(ImGui::GetItemRectMin().x+(elementButtonSize.x-ImGui::CalcTextSize(symbols[atomicNumber-1].c_str()).x)*0.5,
            ImGui::GetItemRectMin().y+(elementButtonSize.y-ImGui::CalcTextSize(symbols[atomicNumber-1].c_str()).y)*0.5
        ),
        atomicSymbolColor,
        symbols[atomicNumber-1].c_str()
    );
    double symbolSize=ImGui::CalcTextSize(symbols[atomicNumber-1].c_str()).y;
    ImGui::PopFont();

    ImGui::PushFont(nameFont);

    //0.6 is nicer
    draw_list->AddText(
        ImVec2(
            ImGui::GetItemRectMin().x+(elementButtonSize.x-ImGui::CalcTextSize(names[atomicNumber-1].c_str()).x)*0.5,
            ImGui::GetItemRectMin().y+(elementButtonSize.y-ImGui::CalcTextSize(names[atomicNumber-1].c_str()).y)*0.5+symbolSize*0.6
        ),
        atomicNameColor,
        names[atomicNumber-1].c_str()
    );
    ImGui::PopFont();

    ImGui::PushFont(massFont);
    draw_list->AddText(
        ImVec2(
            ImGui::GetItemRectMin().x+(elementButtonSize.x-ImGui::CalcTextSize(std::to_string(masses[atomicNumber-1]).c_str()).x)*0.5,
            ImGui::GetItemRectMax().y-ImGui::CalcTextSize(std::to_string(masses[atomicNumber-1]).c_str()).y-elementButtonBorderThickness
        ),
        atomicMassColor,
        std::to_string(masses[atomicNumber-1]).c_str()
    );
    ImGui::PopFont();

    //idk but 8 is optimum so funny
    //size chnage should only happen once a frame
    //initialButtonCorner.x-=sizeChange;
    ImGui::PushStyleColor(ImGuiCol_Text,customElementPopUpTextColor);
    ImGui::PushStyleColor(ImGuiCol_WindowBg,customElementPopUpBackgroundColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBg,customElementPopUpTitleBarColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive,customElementPopUpActiveTitleBarColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed,customElementPopUpCollapsedTitleBarColor);

    if(showCustomElementPopUp && atomicNumber==customElementAtomicNumber){
        ImGui::OpenPopup("Custom Element");
        double atomicMass=masses[atomicNumber-1];
        int charge =0;
        if(ImGui::BeginPopupModal("Custom Element",nullptr,ImGuiWindowFlags_AlwaysAutoResize)){
            ImGui::Text("Enter desired Atomic Mass: ");
            bool AM=ImGui::InputDouble("Atomic Mass", &atomicMass);
    
            ImGui::Separator();
    
            ImGui::Text("Enter desired Charge: ");
            bool C=ImGui::InputInt("Charge", &charge);
    
            if((C || AM)&&ImGui::IsKeyPressed(ImGuiKey_Enter)){
                ImGui::CloseCurrentPopup();
                CompoundObject(atomicNumber,atomicMass,charge);
                showCustomElementPopUp=false;
            }
        }
        ImGui::EndPopup();
    }
    ImGui::PopStyleColor(5);
}

void UI::GenerateCompoundButton(int compoundNumber, double sizeChange,ImFont* compoundNameFont,ImFont* molecularFormulaFont, bool isFirstBox){

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    Compound comp(molecules[compoundNumbers[compoundNumber-1]]);
    std::string formula=comp.getMolecularFormula();

    //You Can:t Change Staticness
    static ImVec2 initialButtonCorner = ImGui::GetCursorScreenPos();
    static ImVec2 buttonCorner = ImGui::GetCursorScreenPos();

    if(sizeChange && isFirstBox){
        initialButtonCorner.x=ImGui::GetCursorScreenPos().x;
        buttonCorner.x=ImGui::GetCursorScreenPos().x;
    }

    float remainingSpace=io.DisplaySize.x-buttonCorner.x-elementButtonSize.x;
    if(remainingSpace>compoundButtonSize.x && !isFirstBox){
        ImGui::SetCursorScreenPos(ImVec2(buttonCorner.x+compoundButtonSize.x,buttonCorner.y));
    }
    else if(!isFirstBox){
        ImGui::SetCursorScreenPos(ImVec2(initialButtonCorner.x,buttonCorner.y+compoundButtonSize.y));
    }

    buttonCorner = ImGui::GetCursorScreenPos();

    draw_list->AddRectFilled(
        buttonCorner,
        ImVec2(buttonCorner.x + compoundButtonSize.x, buttonCorner.y + compoundButtonSize.y),
        compoundButtonColors[compoundNumber-1],
        compoundButtonCurve
    );
    
    ImGui::InvisibleButton(std::to_string(compoundNumber).c_str(), compoundButtonSize);

    if (ImGui::IsItemHovered()) {
        draw_list->AddRectFilled(
            buttonCorner,
            ImVec2(buttonCorner.x + compoundButtonSize.x, buttonCorner.y + compoundButtonSize.y),
            compoundButtonHoveredColors[compoundNumber-1],
            compoundButtonCurve
        ); 
    }
    if (ImGui::IsItemClicked()) {
        draw_list->AddRectFilled(
            buttonCorner,
            ImVec2(buttonCorner.x + compoundButtonSize.x, buttonCorner.y + compoundButtonSize.y),
            compoundButtonClickedColors[compoundNumber-1],
            compoundButtonCurve
        ); 
        CompoundObject(compoundNumber,'h');
    }

    draw_list->AddRect(buttonCorner,
        ImVec2(buttonCorner.x + compoundButtonSize.x, buttonCorner.y + compoundButtonSize.y), compoundButtonBorderColor, compoundButtonCurve,
        0, 
        compoundButtonBorderThickness
    );
    

    ImGui::PushFont(compoundNameFont);
    draw_list->AddText(
        ImVec2(ImGui::GetItemRectMin().x+(compoundButtonSize.x-ImGui::CalcTextSize(compoundNumbers[compoundNumber-1].c_str()).x)*0.5,
            ImGui::GetItemRectMin().y+(compoundButtonSize.y-ImGui::CalcTextSize(compoundNumbers[compoundNumber-1].c_str()).y)*0.5
        ),
        compoundNameColor,
        compoundNumbers[compoundNumber-1].c_str()
    );
    double nameSize=ImGui::CalcTextSize(compoundNumbers[compoundNumber-1].c_str()).y;
    ImGui::PopFont();

    ImGui::PushFont(molecularFormulaFont);
    draw_list->AddText(
        ImVec2(
            ImGui::GetItemRectMin().x+(compoundButtonSize.x-ImGui::CalcTextSize(formula.c_str()).x)*0.5,
            ImGui::GetItemRectMin().y+(compoundButtonSize.y-ImGui::CalcTextSize(formula.c_str()).y)*0.5+nameSize
        ),
        molecularFormulaColor,
        formula.c_str()
    );
    ImGui::PopFont();


}

void UI::SearchBar(ImFont* searchFontSmall, ImFont* searchFontLarge,std::vector<std::string>& currentSearchArray){

    static double searchBarHeightPerCent=initialSearchBarHeightPerCent;

    ImGui::PushStyleColor(ImGuiCol_FrameBg, searchBarColor);  
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, searchBarHoveredColor);  
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, searchBarTypingColor);  

    ImGui::PushStyleColor(ImGuiCol_Text, searchBarTextColor);  

    static std::vector<char> buffer(62, '\0');
    static std::string searchQuery;
    std::strncpy(buffer.data(), searchQuery.c_str(), buffer.size());

    ImGui::SetNextItemWidth(ImGui::GetWindowSize().x);
    ImGui::SetCursorPos(ImVec2(0,ImGui::GetWindowSize().y-ImGui::GetWindowSize().y*searchBarHeightPerCent)); 

    if(ImGui::GetWindowSize().y>largeWindowHeight){
        ImGui::PushFont(searchFontLarge);
    }
    else{
        ImGui::PushFont(searchFontSmall);
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 0.0f);
    ImGui::InputTextMultiline("##Search", buffer.data(), buffer.size(),ImVec2(ImGui::GetWindowSize().x,ImGui::GetWindowSize().y*searchBarHeightPerCent),ImGuiInputTextFlags_CallbackCharFilter,FilterCharactersSearchBar);
    ImGui::PopStyleVar();
    searchQuery = std::string(buffer.data());

    std::transform(searchQuery.begin(),searchQuery.end(),searchQuery.begin(),::tolower);
 
    if(searchQuery.size()==0){
        ImVec2 placeholderPos = ImGui::GetItemRectMin();
        ImGui::SetCursorScreenPos(ImVec2(placeholderPos.x, placeholderPos.y)); 
        LoadMagnifyingGlass(searchBarHeightPerCent);

        placeholderPos = ImGui::GetItemRectMin();
        ImGui::SetCursorScreenPos(ImVec2(placeholderPos.x + search___padding+ImGui::GetWindowSize().y*searchBarHeightPerCent, placeholderPos.y +search___padding));
        ImGui::PushStyleColor(ImGuiCol_Text, searchBarLabelColor); 
        ImGui::TextUnformatted(searchBarLabel);
        ImGui::PopStyleColor();

        currentSearchArray=searchBar;
    }
    else{
        currentSearchArray.clear();
        for(auto it: searchBar){
            if(strstr(it.c_str(),searchQuery.c_str())!=NULL){
                currentSearchArray.push_back(it);
            }
        }   
    }

    ImGui::PopFont();
    ImGui::PopStyleColor(4);
}

void UI::LoadMagnifyingGlass(double searchBarHeightPerCent){

    int width, height, channels;
    unsigned char* data = stbi_load(SearchGlass, &width, &height, &channels, 4);

    if (!data){
        printf("Failed to load image: %s\n", SearchGlass);
        return;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    ImGui::Image((void*)(intptr_t)texture, ImVec2(ImGui::GetWindowSize().y*searchBarHeightPerCent,ImGui::GetWindowSize().y*searchBarHeightPerCent),ImVec2(0, 0), ImVec2(1, 1),searchGlassTransparency);
}

int UI::FilterCharactersSearchBar(ImGuiInputTextCallbackData* data){
    if (strchr(disallowedCharSearchBar, data->EventChar)){
        return 1;
    } 
    return 0;   
}

void UI::TopMenu(){

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    static std::string fileName="Unknown";

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

            if (ImGui::MenuItem("Undo", "CTRL+Z")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_Z))){

            }
            if (ImGui::MenuItem("Redo", "CTRL+Y")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_Y))){
                // bg;
            }

            ImGui::Separator(); 
            
            if (ImGui::MenuItem("Cut", "CTRL+X")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_X))){
                // bg;
            }
            if (ImGui::MenuItem("Copy", "CTRL+C")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_C))){
                // bg;
            }
            if (ImGui::MenuItem("Paste", "CTRL+V")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_V))){ 
                // bg;
            }
            if(ImGui::MenuItem("Hydrogen Filler")){
                auto list=Compound::getListOfCompounds();
                for(auto it: list){
                    it->hydrogenFiller();
                }
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
            if(openFile){
                open(fileName);
            }
        }        

        ImGui::PopStyleColor(5);

        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX()+topMenu_____Padding);
        if(ImGui::Button("Save")||(ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsKeyPressed(ImGuiKey_S))){
            if(fileName=="Unknown"){
                saveAs(fileName);
            }        
            else{
                save(fileName);
            }
        }         

        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX()+topMenu_____Padding);
        if(ImGui::Button("Save As")||(ImGui::IsKeyDown(ImGuiMod_Ctrl)&& (ImGui::IsKeyPressed(ImGuiKey_LeftShift)||ImGui::IsKeyPressed(ImGuiKey_RightShift)) && ImGui::IsKeyPressed(ImGuiKey_S))){
            saveAs(fileName);
        }            

        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX()+topMenu_____Padding);
        if(ImGui::Button("Help")){
            openHelpLink();
        }

        ImGui::PushStyleColor(ImGuiCol_Text,fileNameColor);
        ImGui::SameLine();
        ImGui::SetCursorPosX(io.DisplaySize.x-topMenu_____Padding-ImGui::CalcTextSize((std::string("Current File: ")+fileName).c_str()).x);
        ImGui::Text("%s",(std::string("Current File: ")+fileName).c_str());

        ImGui::PopStyleColor();
        ImGui::EndMainMenuBar();
    }

    ImGui::PushStyleColor(ImGuiCol_Text,settingsColorPickersTextColor);
    ImGui::PushStyleColor(ImGuiCol_WindowBg,settingsColorPickersBackgroundColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBg,settingsColorPickersTitleBarColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive,settingsColorPickersActiveTitleBarColor);
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed,settingsColorPickersCollapsedTitleBarColor);

    if(showBackgroundColor){
        ImGui::Begin("Background Color Picker", &showBackgroundColor);
        ImGui::ColorEdit4("Background Color", (float*)&windowColor);
        ImGui::End();
    }
    if(showTopMenuColor){
        ImGui::Begin("Top Menu Color Picker", &showTopMenuColor);
        ImGui::ColorEdit4("Top Menu Color", (float*)&topMenuButtonColor);//text 
        ImGui::End();
    }
    if(showTopMenuTextColor){
        ImGui::Begin("Top Menu Text Color Picker", &showTopMenuTextColor);
        ImGui::ColorEdit4("Top Menu Text Color", (float*)&topMenuTextColor);//text 
        ImGui::End();
    }
    if(showElementColor){
        ImGui::Begin("Element Tab Color Picker", &showElementColor);
        ImGui::ColorEdit4("Element Tab Color", (float*)&elementWindowColor);//text 
        ImGui::End();
    }
    if(showElementTextColor){
        ImGui::Begin("Element Text Color Picker", &showElementTextColor);
        ImGui::ColorEdit4("Element Text Color", (float*)&elementWindowTextColor);//text 
        ImGui::End();
    }
    if(showElementBoxColor){
        ImGui::Begin("Element Box Color Picker", &showElementBoxColor);
        ImGui::ColorEdit4("Element Box Color", (float*)&elementButtonColor);//text 
        ImGui::End();
    }
    if(showCompoundColor){
        ImGui::Begin("Compound Tab Color Picker", &showCompoundColor);
        ImGui::ColorEdit4("Compound Tab Colorr", (float*)&compoundWindowColor);//text 
        ImGui::End();
    }
    if(showCompoundTextColor){
        ImGui::Begin("Compound Text Color Picker", &showCompoundTextColor);
        ImGui::ColorEdit4("Compound Text Color", (float*)&compoundWindowTextColor);//text 
        ImGui::End();
    }
    if(showCompoundBoxColor){
        ImGui::Begin("Compound Box Color Picker", &showCompoundBoxColor);
        ImGui::ColorEdit4("Compound Box Color", (float*)&compoundWindowColor);//text 
        ImGui::End();
    }
    if(showScrollColor){
        ImGui::Begin("Scroll Bar Color Picker", &showScrollColor);
        ImGui::ColorEdit4("Scroll Bar Color", (float*)&scrollBarColor);//text 
        ImGui::End();
    }
    if(showSearchColor){
        ImGui::Begin("Search Bar Color Picker", &showSearchColor);
        ImGui::ColorEdit4("Search Bar Color", (float*)&searchBarColor);//text 
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
            CompoundObject* obj=new CompoundObject(compoundString); 
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
                    std::cerr << "Error opening file." << std::endl;
                    free(outPath);
                    return;
                }
                
                std::string line;
                while (std::getline(file, line))
                {
                    CompoundObject* obj=new CompoundObject(line);
                }

                file.close();
                free(outPath);  
        
        }
        else if (result == NFD_CANCEL)
        {
            std::cout << "User canceled.\n";
        }
        else
        {
            std::cout << "Error opening file dialog.\n";
        }
        showInsertFile=!showInsertFile;
    }

    ImGui::PopStyleColor(4);

    ImGui::PopStyleColor(7);
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

void UI::saveAs(std::string& fileName){ 
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

    if (result == NFD_OKAY)
    {
        if ((std::string(outPath).size()) < 4 || std::string(outPath).substr(std::string(outPath).size() - 4) != ".txt"){
            fileName=outPath+std::string(".txt");
        }
        else{
            fileName=outPath;
        }

        std::ofstream file(outPath);

        if (!file.is_open()){
            std::cerr << "Error opening file." << std::endl;
            free(outPath);
            return;
        }
        
        std::string line;
        auto list=Compound::getListOfCompounds();
        for(auto it: list){
            file<<(it->getCompoundString()).c_str()<<std::endl;
        }
            
        file.close();
        free(outPath);  
    }
    else if (result == NFD_CANCEL)
    {
        std::cout << "User canceled.\n";
    }
    else
    {
        std::cout << "Error opening file dialog.\n";
    }
}

void UI::save(std::string& fileName){

    std::ofstream file(fileName);
    if (!file.is_open()){
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    std::string line;
    auto list=Compound::getListOfCompounds();
    for(auto it: list){
        file<<(it->getCompoundString()).c_str()<<std::endl;
    }

    file.close();
}

void UI::open(std::string& fileName){
    
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

    if (result == NFD_OKAY && std::string(outPath).size() < 4 && (std::string(outPath).substr(std::string(outPath).size() - 4) != ".txt")){
        std::ifstream file(outPath);
        if (!file.is_open()){
            std::cerr << "Error opening file." << std::endl;
            free(outPath);
            return;
        }
        
        std::string line;
        auto list=CompoundObject::getListOfCompoundObjects();
        for(auto it: list){
            free(it);
        }

        while (std::getline(file, line)){
            CompoundObject* obj=new CompoundObject(line);
        }
        fileName=outPath;

        file.close();
        free(outPath);  
    }
    else if (result == NFD_CANCEL){
        std::cout << "User canceled.\n";
    }
    else{
        std::cout << "Error opening file dialog.\n";
    }

}

