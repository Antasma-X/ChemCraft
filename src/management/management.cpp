#include "management.h"

void Management::glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


void Management::OpenFile(){
    std::ifstream file(currentFile);

    if(!file){
        error->Push("File could not be opened");
        std::cerr<<"File could not be opened"<<std::endl;
        currentFile="Unknown";
    }
    else{
        std::string line;
        while (std::getline(file, line)){
            Compound* comp;
            try{
                comp=new Compound(line);
                Render::createCompoundObject(comp); 
            }
            catch(std::invalid_argument& e){
                error->Push(line+ " is Invalid");
                std::cerr<<line<<" is Invalid"<<std::endl;
            }    
        }
        file.close();
    }
}

GLFWwindow* Management::SetUp(){

    GLFWwindow* window=nullptr;
    camera = new Camera();
    error= new Error();
    //GLFW Setup 
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()){
        std::cerr<<"GLFW Failed to Initialize"<<std::endl;
        return window;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    std::cout<<"heybal"<<std::endl;
    window = glfwCreateWindow(windowWidth, windowHeight, windowName, nullptr, nullptr);
    if (window == nullptr){
        std::cerr<<"GLFW Window Could not Open"<<std::endl;
        glfwTerminate();
        return window;
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

    //OpenGl Set Up
    const char* glsl_version = "#version 330";
    ImGui_ImplGlfw_InitForOpenGL(window, false);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
    glDisable(GL_DEPTH_TEST);
    std::cout<<"heybal"<<std::endl;
    glEnable(0x8642);

    //might get fukced
    //Shaders
    Shader elementShader= Shader(elementVertShaderFilePath,elementFragShaderFilePath);
    Shader electronShader= Shader(electronVertShaderFilePath,electronFragShaderFilePath);
    Shader numberShader= Shader(numberVertShaderFilePath,numberFragShaderFilePath);
    Shader signShader= Shader(signVertShaderFilePath,signFragShaderFilePath);

    Shader covalentShader= Shader(covalentVertShaderFilePath,covalentFragShaderFilePath);
    Shader dativeShader= Shader(dativeVertShaderFilePath,dativeFragShaderFilePath);
    Shader ionicShader=Shader(ionicVertShaderFilePath,ionicFragShaderFilePath);

    // SignObject::colorLocation=glGetUniformLocation(signShader.shaderProgram,"color");

    shaders["electron"]=electronShader;
    shaders["element"]=elementShader;
    shaders["number"]=numberShader;
    shaders["sign"]=signShader;

    shaders["covalent"]=covalentShader;
    shaders["dative"]=dativeShader;
    shaders["ionic"]=ionicShader;

    SetCallBacks(window);
    
    return window;
}

void Management::SetCallBacks(GLFWwindow* window){
    glfwSetWindowUserPointer(window, camera);
    glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
    glfwSetKeyCallback(window, Callbacks::KeyCallBack);
    glfwSetScrollCallback(window, Callbacks::ScrollCallback);
    glfwSetMouseButtonCallback(window, Callbacks::MouseButtonCallback);
    glfwSetCursorPosCallback(window, Callbacks::CursorPosCallback);
    glfwSetFramebufferSizeCallback(window, Callbacks::FrameSizeCallback);
}

void Management::CleanUp(GLFWwindow* window){
//cleanup all objects after rendering figured out
    // for(auto it: )


    // for(auto [key,value]:shaders){
    //     value.Delete();
    //     free(&value);
    // }

    delete error;
    delete camera;
    
    //ImGui Ending
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    //GLFW Ending
    glfwDestroyWindow(window);
    glfwTerminate();
}