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
            if(!(i>118)){
                std::string lowerName=names[i-1];
                std::transform(lowerName.begin(),lowerName.end(),lowerName.begin(),::tolower);
    
                std::string lowerSymbol=symbols[i-1];
                std::transform(lowerSymbol.begin(),lowerSymbol.end(),lowerSymbol.begin(),::tolower);
    
                if(std::find(currentSearchArray.begin(),currentSearchArray.end(),lowerName)!=currentSearchArray.end()||std::find(currentSearchArray.begin(),currentSearchArray.end(),lowerSymbol)!=currentSearchArray.end()){
                    GenerateElementButton(i,sizeChange,numberFont, symbolFont, nameFont, massFont,isFirstBox);
                    isFirstBox=false;
                }   
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
        if(elementHeight<io.DisplaySize.y*minimumChildWindowPerCent){
            elementHeight+=adjustOffset;
            compoundHeight-=adjustOffset;
        }
        else if(compoundHeight<io.DisplaySize.y*minimumChildWindowPerCent){
            compoundHeight+=adjustOffset;
            elementHeight-=adjustOffset;
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
            std::string lowerName=compoundNumbers[i-1];
            std::transform(lowerName.begin(),lowerName.end(),lowerName.begin(),::tolower);

            if(std::find(currentSearchArray.begin(),currentSearchArray.end(),lowerName)!=currentSearchArray.end()){
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
        
        Compound* comp;
        try{
            comp=new Compound(atomicNumber);
            Render::createCompoundObject(comp); 
        }
        catch(std::invalid_argument& e){
            isError=true;
            errorMessage=std::to_string(atomicNumber)+" is Invalid";
            std::cerr<<atomicNumber<<" is Invalid"<<std::endl;
        }    
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
                Compound* comp;
                try{
                    comp=new Compound(atomicNumber,atomicMass,charge);
                    Render::createCompoundObject(comp); 
                }
                catch(std::invalid_argument& e){
                    isError=true;
                    errorMessage=std::to_string(atomicNumber)+" is Invalid";
                    std::cerr<<std::to_string(atomicNumber)<<" is Invalid"<<std::endl;
                }    

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

    std::string formula;
    try{
        Compound comp(molecules[compoundNumbers[compoundNumber-1]]);
        formula=comp.getMolecularFormula();
    }
    catch(std::invalid_argument& e){
        return;
    }

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
        try{
            Compound* newComp= new Compound(molecules[compoundNumbers[compoundNumber-1]]);
            Render::createCompoundObject(newComp);
        }
        catch(std::invalid_argument& e){
            isError=true;
            errorMessage="Invalid Compound String in Compound List";
            std::cerr<<"Invalid Compound String in Compound List"<<std::endl;
        }

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

    stbi_set_flip_vertically_on_load(false);
    int width, height, channels;
    unsigned char* data = stbi_load(SearchGlass, &width, &height, &channels, 4);

    if (!data){
        isError=true;
        errorMessage="Failed to load Search Glass Image";
        std::cerr<<"Failed to load image: "<< SearchGlass<<std::endl;

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