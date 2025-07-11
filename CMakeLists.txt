cmake_minimum_required(VERSION 3.20)
project(Nomenclature)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# add_compile_options(
#     # -Wall
#     # -Wextra
#     # -Wpedantic
#     # -Wshadow
#     # -fsanitize=address
#     # -O2
# )


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})  
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)




file(GLOB SOURCES "src/*.cpp" "src/chemistry/*.cpp" "src/graphics/*.cpp" "src/render/*.cpp" "src/UI/*.cpp" "src/management/*.cpp" "src/objects/*.cpp")


find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(lib/imgui)
add_subdirectory(lib/nativefiledialog)
add_subdirectory(lib/stb_image)
add_subdirectory(lib/json)

add_executable(cute ${SOURCES})


target_link_libraries(cute PUBLIC glfw)
target_link_libraries(cute PUBLIC OpenGL::GL)



target_link_libraries(cute PRIVATE imgui)
target_link_libraries(cute PRIVATE nativefiledialog)
target_link_libraries(cute PRIVATE stb_image)
target_link_libraries(cute PRIVATE json)


target_include_directories(cute PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(cute PRIVATE ${CMAKE_SOURCE_DIR}/include/chemistry)
target_include_directories(cute PRIVATE ${CMAKE_SOURCE_DIR}/include/UI)
target_include_directories(cute PRIVATE ${CMAKE_SOURCE_DIR}/include/render)
target_include_directories(cute PRIVATE ${CMAKE_SOURCE_DIR}/include/graphics)
target_include_directories(cute PRIVATE ${CMAKE_SOURCE_DIR}/include/management)
target_include_directories(cute PRIVATE ${CMAKE_SOURCE_DIR}/include/objects)