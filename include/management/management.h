#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "render.h"
#include "callbacks.h"
#include "utils.h"

namespace Management{

    /*
    Sets up all the callbacks so you can move around, zoom in, etc for the actual app
    */
    static void SetCallBacks(GLFWwindow* window);

    //Clipboard function for pasting
    static const char* My_GetClipboardText(void* user_data);

    //Clipboard function for copying
    static void My_SetClipboardText(void* user_data, const char* text);

    /*
    Opens file passed in main and makes it current
    Gets the compound strings from it
    */
    void OpenFile();

    /*
    Sets up GLFW, OpenGL, ImGui
    Creates Shaders

    Returns:nullptr if failure
            window pointer if succeeds
    */
    GLFWwindow* SetUp();

    /*
    Cleans up GLFW, OpenGL, ImGui and cleans up objects
    */
    void CleanUp(GLFWwindow* window);
}
#endif