#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "camera.h"
#include "render.h"
 
namespace Callbacks{

    /*
    These 2 variables are used in the CursorPosCallback and MouseButtonCallback to move around the screen
    In MouseButtonCallback, dragging is set to true when the left mouse button is clicked and set to false when released
    When dragging is true CursorPosCallback actually shifts the camera's position and moves around
    */ 
    extern bool dragging;
    extern glm::vec2 lastMousePos;

    extern ElementObject* selectedObject;

    extern glm::vec2 dragOffset;

    /*
    These are the callbacks regesitered by glfw to enable actual interaction
    When needed, ImGui callback is also called when the UI is being accessed
    */ 

    void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

    void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

    void FrameSizeCallback(GLFWwindow* window, int width, int height);

    static glm::vec2 getMouseWorldPos(double mouseX, double mouseY, Camera& cam);
}
#endif
