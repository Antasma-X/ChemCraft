cmake_minimum_required(VERSION 3.20)
project(Nomenclature)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
file(GLOB SOURCES "src/*.cpp")



find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)


add_executable(cute test/window.cpp ${SOURCES})


target_link_libraries(cute glfw)
target_link_libraries(cute OpenGL::GL)


add_subdirectory(lib)
target_link_libraries(cute imgui)
target_include_directories(cute INTERFACE ../include)

