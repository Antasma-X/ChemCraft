#include "management.h"
 
void Management::SetCallBacks(GLFWwindow* window){
    glfwSetWindowUserPointer(window, camera);
    glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
    glfwSetKeyCallback(window, Callbacks::KeyCallBack);
    glfwSetScrollCallback(window, Callbacks::ScrollCallback);
    glfwSetMouseButtonCallback(window, Callbacks::MouseButtonCallback);
    glfwSetCursorPosCallback(window, Callbacks::CursorPosCallback);
    glfwSetFramebufferSizeCallback(window, Callbacks::FrameSizeCallback);
}
 
const char* Management::My_GetClipboardText(void* user_data) {
    return glfwGetClipboardString((GLFWwindow*)user_data);
}

void Management::My_SetClipboardText(void* user_data, const char* text) {
    glfwSetClipboardString((GLFWwindow*)user_data, text);
}
 
void Management::OpenFile(){
    std::ifstream file(currentFile);

    if(!file){
        error->push("File could not be opened");
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
                error->push(line+ " is Invalid");
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
    glfwSetErrorCallback(Callbacks::glfw_error_callback);
    if (!glfwInit()){
        std::cerr<<"GLFW Failed to Initialize"<<std::endl;
        return window;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    window = glfwCreateWindow(windowWidth, windowHeight, windowName, nullptr, nullptr);
    if (window == nullptr){
        std::cerr<<"GLFW Window Could not Open"<<std::endl;
        glfwTerminate();
        return window;
    }
    
    glfwSetWindowAttrib(window, GLFW_FLOATING, GLFW_FALSE);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return nullptr;
    }

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

    io.SetClipboardTextFn = My_SetClipboardText;
    io.GetClipboardTextFn = My_GetClipboardText;
    io.ClipboardUserData = window;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glEnable(0x8642); //idr why i did this but im not messing with it

    //Shaders
    Shader elementShader= Shader(elementVertShaderFilePath,elementFragShaderFilePath);
    Shader glowElementShader=Shader(glowElementVertShaderFilePath,glowElementFragShaderFilePath);
    Shader electronShader= Shader(electronVertShaderFilePath,electronFragShaderFilePath);
    Shader glowElectronShader=Shader(glowElectronVertShaderFilePath,glowElectronFragShaderFilePath);
    Shader numberShader= Shader(numberVertShaderFilePath,numberFragShaderFilePath);
    Shader signShader= Shader(signVertShaderFilePath,signFragShaderFilePath);

    Shader covalentShader= Shader(covalentVertShaderFilePath,covalentFragShaderFilePath);
    Shader dativeShader= Shader(dativeVertShaderFilePath,dativeFragShaderFilePath);
    Shader ionicShader=Shader(ionicVertShaderFilePath,ionicFragShaderFilePath);
    Shader glowBondShader=Shader(glowBondVertShaderFilePath,glowBondFragShaderFilePath);
    
    shaders["electron"]=electronShader;
    shaders["glowElectron"]=glowElectronShader;
    shaders["glowElement"]=glowElementShader;
    shaders["element"]=elementShader;
    shaders["number"]=numberShader;
    shaders["sign"]=signShader;
 
    shaders["covalent"]=covalentShader;
    shaders["dative"]=dativeShader;
    shaders["ionic"]=ionicShader;
    shaders["glowBond"]=glowBondShader;

    SetCallBacks(window);
    
    return window;
}
 

void Management::CleanUp(GLFWwindow* window){

    for(auto it: Compound::getListOfCompounds()){
        delete it;
    }

    for(auto [key,value]: ElementObject::getAllElementObjects()){
        delete value;
    }

    for(auto it: BondObject::getAllBondObjects()){
        delete it;
    }
    
    for(auto [key,value]:shaders){
        value.Delete();
    }

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

