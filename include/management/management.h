#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"
#include "config.h"
#include "render.h"
#include "signObject.h"
#include "error.h"

namespace Management{
    /*
    Called when GLFW has error
    */
    static void glfw_error_callback(int error, const char* description);

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
    Cleans up GLFW, ImGui and cleans up objects
    */
    void CleanUp(GLFWwindow* window);
}
#endif