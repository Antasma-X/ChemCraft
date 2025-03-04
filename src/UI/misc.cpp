#include "UIGeneration.h"

void UI::ErrorPopUp(){
    static ImGuiIO& io = ImGui::GetIO(); (void)io;
    if(isError){
        ImGui::SetNextWindowPos(ImVec2(0+errorMessageOffsetX,io.DisplaySize.y+errorMessageOffsetY),ImGuiCond_Always, ImVec2(0.0f, 1.0f));
        ImGui::OpenPopup("Error");
        if (ImGui::BeginPopup("Error", ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::TextWrapped("%s", errorMessage.c_str());
            if (ImGui::Button("OK")) {
                isError=false;
                errorMessage="";
                ImGui::CloseCurrentPopup();
            } 
        }
        ImGui::EndPopup();
    }
}