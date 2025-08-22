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
    extern bool isDragging;
    extern glm::vec2 lastMouseWorldPos;
 
    extern std::set<ElementObject*> selectedElementObjects;
    extern std::set<ElementObject*> hoveredElementObjects;
    extern bool isElementsDragging;
    
    extern std::set<ElectronObject*> selectedElectronObjects;
    extern std::set<ElectronObject*> hoveredElectronObjects;
    extern bool isElectronDragging;

    extern std::set<ElectronObject*> selectedDativeObjects;
    extern std::set<ElectronObject*> hoveredDativeObjects;
    extern bool isDativeDragging;

    extern std::set<BondObject*> selectedBondObjects;
    extern std::set<BondObject*> hoveredBondObjects;

    //Filters characters allowed in compound name
    static int filterCharactersCompoundName(ImGuiInputTextCallbackData* data);

    //Gets world pos of mouse using xpos, ypos and camera passed in
    static glm::vec2 getMouseWorldPos(double mouseX, double mouseY, Camera& cam);

    /*
    Copies current compounds' strings on screen and then removes them
    */
    void cut();

    /*
    Copies current compounds' strings on screen 
    */
    void copy();
    
    /*
    Pastes compounds from clipBoard
    */
    void paste();

    //Opens context menu when right clicking. Called in main loop
    void openContextMenu();

    /* 
    Called when GLFW has error
    */
    void glfw_error_callback(int error, const char* description);

    /*
    These are the callbacks regesitered by glfw to enable actual interaction
    When needed, ImGui callback is also called when the UI is being accessed
    */ 

    void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

    void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

    void FrameSizeCallback(GLFWwindow* window, int width, int height);
}
#endif
 