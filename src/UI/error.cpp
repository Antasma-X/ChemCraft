#include "error.h"

Error* error= nullptr;

void Error::push(std::string errorString){
    errorStrings.push(errorString);
}

void Error::errorPopUp(){
    static ImGuiIO& io = ImGui::GetIO(); (void)io;

    if(errorStrings.empty()){
        return;
    }
    std::cout<<errorStrings.size()<<std::endl;
    ImGui::SetNextWindowPos(ImVec2(errorMessageOffsetX,io.DisplaySize.y-errorMessageOffsetY),ImGuiCond_Always, ImVec2(0.0f, 1.0f));
    ImGui::SetNextWindowSize(ImVec2(300.0f, 0.0f));

    if (ImGui::Begin("Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove)) {
        ImGui::TextWrapped("%s", errorStrings.top().c_str());

        if (ImGui::Button("OK")) {
            errorStrings.pop();
        }
    }

    ImGui::End();
}


