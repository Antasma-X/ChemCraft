
#include "UIGeneration.h"
#include "compoundRender.h"

#define GL_SILENCE_DEPRECATION




// #if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
// #pragma comment(lib, "legacy_stdio_definitions")
// #endif













static void glfw_error_callback(int error, const char* description);



int main(){

    //GLFW Setup
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()){
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowName, nullptr, nullptr);
    if (window == nullptr){
        std::cout<<"GLFW Window Could not Open"<<std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    //Imgui Setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    

    //Font Setup
    //might chnahe font sizes entierly
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

    //Idk why
    const char* glsl_version = "#version 330";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    //App Loop
    while (!glfwWindowShouldClose(window)){

        //GLFW Stuff
        glfwPollEvents();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0,windowWidth,windowHeight);
        glClearColor(windowColor.x * windowColor.w, windowColor.y * windowColor.w, windowColor.z * windowColor.w, windowColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

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
        UI::TopMenu();

        //SideMenu for elements
        UI::SideMenu(searchFontSmall,searchFontLarge,childWindowSmallFont,childWindowLargeFont, numberFont, symbolFont, nameFont,massFont,compoundNameFont,molecularFormulaFont);
        
        //Draws all elements to screen
        // Render::DrawCompounds

        ImGui::PopFont();
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


    //ImGui Ending
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    //GLFW Ending
    glfwDestroyWindow(window);
    glfwTerminate();
}

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
















