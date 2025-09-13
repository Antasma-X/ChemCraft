#ifndef GUI_DEPENDENCIES_H
#define GUI_DEPENDENCIES_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
    #include <shellapi.h>
#else
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
#endif

#include "stb_image.h"
#include "nfd.h"

#endif

