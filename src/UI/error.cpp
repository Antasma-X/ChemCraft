#include "error.h"

void Error::Push(std::string errorString){
    errorStrings.push(errorString);
}

void Error::ErrorPopUp(){
    static ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    if(errorStrings.size()!=0){
        ImGui::SetNextWindowPos(ImVec2(errorMessageOffsetX,io.DisplaySize.y+errorMessageOffsetY),ImGuiCond_Always, ImVec2(0.0f, 1.0f));
        ImGui::SetNextWindowSize(ImVec2(300.0f, 0.0f));
        ImGui::OpenPopup("Error");
        if (ImGui::BeginPopup("Error", ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::TextWrapped("%s", errorStrings.top().c_str());
            if (ImGui::Button("OK")) {
                errorStrings.pop();
                ImGui::CloseCurrentPopup();
            } 
        }
        ImGui::EndPopup();
    } 
}