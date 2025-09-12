
#include "UIGeneration.h"
#include "render.h"
#include "shader.h"
#include "management.h"
#define GL_SILENCE_DEPRECATION

int main(int argc, char* argv[]){
//need quotes for space in path

    try{
        if(!Config()){
            return 1;
        }
    }
    catch(const nlohmann::json::out_of_range& e){
        std::cerr<<"One or more variables could not be found in either files"<<std::endl<<"Please Redownload original default config json file"<<std::endl;
        throw;
        return 1;
    }
    catch(const std::exception& e){
        std::cerr<<"Idk what happened"<<std::endl;
        throw;
        return 1;
    }

    //putting try here is useless
    GLFWwindow* window= Management::SetUp();
    if(window==nullptr){
        return 1;
    }

    if(argc>1){
        if(argc>2){
            std::cerr<<"Only First File will be counted"<<std::endl;
        }
        currentFile=argv[1];
        Management::OpenFile();
    }

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    //Font Setup
    ImFont* windowSmallFont=io.Fonts->AddFontFromFileTTF(fontFile, windowSmallFontSize);
    ImFont* windowBigFont=io.Fonts->AddFontFromFileTTF(fontFile, windowLargeFontSize);

    ImFont* searchFontSmall= io.Fonts->AddFontFromFileTTF(fontFile, searchSmallFontSize);
    ImFont* searchFontLarge= io.Fonts->AddFontFromFileTTF(fontFile, searchLargeFontSize);

    ImFont* childWindowSmallFont=io.Fonts->AddFontFromFileTTF(fontFile, childWindowSmallFontSize);
    ImFont* childWindowLargeFont=io.Fonts->AddFontFromFileTTF(fontFile, childWindowLargeFontSize);

    ImFont* numberFont=io.Fonts->AddFontFromFileTTF(fontFile, numberFontSize);
    ImFont* symbolFont=io.Fonts->AddFontFromFileTTF(fontFile, symbolFontSize);
    ImFont* nameFont=io.Fonts->AddFontFromFileTTF(fontFile, nameFontSize);
    ImFont* massFont=io.Fonts->AddFontFromFileTTF(fontFile, massFontSize);

    ImFont* compoundNameFont=io.Fonts->AddFontFromFileTTF(fontFile, compoundNameSize);
    ImFont* molecularFormulaFont=io.Fonts->AddFontFromFileTTF(molecularFormulaFontFile,molecularFormulaSize,nullptr, ranges);

    //App Loop
    while (!glfwWindowShouldClose(window)){

        //GLFW Stuff
        glfwPollEvents();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0,display_w,display_h);
        glClearColor(windowColor.x * windowColor.w, windowColor.y * windowColor.w, windowColor.z * windowColor.w, windowColor.w);

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
 
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Gives font to window size
        if(io.DisplaySize.y>largeWindowHeight){
            ImGui::PushFont(windowBigFont);
        }
        else{
            ImGui::PushFont(windowSmallFont);
        }

        //Top Menu
        UI::topMenu();

        //SideMenu for elements
        UI::sideMenu(searchFontSmall,searchFontLarge,childWindowSmallFont,childWindowLargeFont, numberFont, symbolFont, nameFont,massFont,compoundNameFont,molecularFormulaFont);
        
        // glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draws all elements to screen
        Render::render();

        if(openContMenu){
            ImGui::OpenPopup("Context Menu");
            openContMenu=false;
        }
        //Renders context menu when right clicking on elements
        Callbacks::openContextMenu(); 

        //Renders error window in corner
        error->errorPopUp();
         
        ImGui::PopFont();

        //ImGui Render(Not my render, learnt that the hard way)
        ImGui::Render();
        
        //Imgui Ending Code
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        //GLFW Ending
        glfwSwapBuffers(window);
    }

    Management::CleanUp(window);
}