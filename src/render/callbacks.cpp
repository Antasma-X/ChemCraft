#include "callbacks.h"

bool Callbacks::dragging = false;
glm::vec2 Callbacks::lastMousePos;

ElementObject* Callbacks::selectedObject;

glm::vec2 Callbacks::dragOffset;

void Callbacks::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){

    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureKeyboard)
        return;

    auto* cam=static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (!cam){
        return;
    }
  
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_LEFT) cam->Move({-minCamMovement, 0});
        if (key == GLFW_KEY_RIGHT) cam->Move({minCamMovement, 0});
        if (key == GLFW_KEY_UP) cam->Move({0, minCamMovement});
        if (key == GLFW_KEY_DOWN) cam->Move({0, -minCamMovement});
    }
}

void Callbacks::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset){

    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;

    auto* cam=static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (!cam){
        return;
    }

    cam->Zoom(1+yoffset*zoomShift);
}

void Callbacks::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods){

    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;
        
    auto* cam=static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (!cam||button != GLFW_MOUSE_BUTTON_LEFT){
        return;
    }

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    glm::vec2 mouseScreen(x, y);
    glm::vec2 mouseWorldPos = getMouseWorldPos(x, y,*cam);

    if (action == GLFW_PRESS){
        selectedObject = Render::getElementClicked(mouseWorldPos);
        if (selectedObject!=nullptr){
            std::cout<<"djfw"<<std::endl;
            dragOffset = mouseWorldPos - selectedObject->position;
            dragging = false; // disable camera drag if object is selected
        } else {
            dragging = true; // drag camera
            lastMousePos = mouseScreen;
        }
    } else if (action == GLFW_RELEASE) {
        selectedObject = nullptr;
        dragging = false;
    }

    // if (action == GLFW_PRESS){
    //     cam->dragging = true;
    //     double x, y;
    //     glfwGetCursorPos(window, &x, &y);
    //     cam->lastMousePos = glm::vec2(x, y);

    // } 
    // else if (action == GLFW_RELEASE){
    //     cam->dragging = false;
    // }
}

void Callbacks::CursorPosCallback(GLFWwindow* window, double xpos, double ypos){

    ImGuiIO& io = ImGui::GetIO();
    
    if (io.WantCaptureMouse)
        return;

    auto* cam=static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (!cam){
        return;
    }
 
    glm::vec2 currentPos(xpos, ypos);

    if (selectedObject!=nullptr) {
        std::cout<<"sexssfsfffffffffffffffff"<<std::endl;
        glm::vec2 mouseWorld = getMouseWorldPos(xpos, ypos, *cam);
        glm::vec2 newPos = mouseWorld - dragOffset;
        glm::vec2 delta = newPos - selectedObject->position;
        selectedObject->Move(delta);

        Render::MoveBonds(selectedObject,delta);
        return;
    }
    if(dragging){
    glm::vec2 delta = (currentPos - lastMousePos) * (1.0f / cam->GetCurrentZoom());

    cam->Move(glm::vec2(-delta.x,-delta.y));

    lastMousePos = currentPos;
    }

}

void Callbacks::FrameSizeCallback(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);

    auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (cam) {
        cam->Resize((float)width, (float)height);
    }

    ImGuiIO& io=ImGui::GetIO();
    io.DisplaySize=ImVec2((float)width, (float)height);
}

glm::vec2 Callbacks::getMouseWorldPos(double mouseX, double mouseY, Camera& cam){
    // Convert screen coordinates to Normalized Device Coordinates (NDC)
    float ndcX = (2.0f * mouseX) / cam.screenWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * mouseY) / cam.screenHeight;

    glm::vec4 clipCoords(ndcX, ndcY, 0.0f, 1.0f);

    // Inverse of projection * view matrix
    glm::mat4 invVP = glm::inverse(cam.GetVP());

    glm::vec4 worldCoords = invVP * clipCoords;

    return glm::vec2(worldCoords);
}
