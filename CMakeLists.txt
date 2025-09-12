cmake_minimum_required(VERSION 3.20)
project(ChemCraft)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(GLOB SOURCES "src/*.cpp" "src/chemistry/*.cpp" "src/graphics/*.cpp" "src/render/*.cpp" "src/UI/*.cpp" "src/management/*.cpp" "src/objects/*.cpp")

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(lib/imgui)
add_subdirectory(lib/nativefiledialog)
add_subdirectory(lib/stb_image)
add_subdirectory(lib/json)

add_executable(ChemCraft ${SOURCES})

target_link_libraries(ChemCraft PUBLIC glfw)
target_link_libraries(ChemCraft PUBLIC OpenGL::GL)
target_link_libraries(ChemCraft PRIVATE imgui)
target_link_libraries(ChemCraft PRIVATE nativefiledialog)
target_link_libraries(ChemCraft PRIVATE stb_image)
target_link_libraries(ChemCraft PRIVATE json)

target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/chemistry)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/UI)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/render)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/graphics)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/management)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/objects)



# --------------------------
# Copy assets automatically
# --------------------------
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# --------------------------
# Platform-specific tweaks
# --------------------------
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
endif()

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif()

# --------------------------
# Packaging with CPack
# --------------------------
install(TARGETS ${PROJECT_NAME} DESTINATION .)

include(CPack)

set(CPACK_PACKAGE_NAME "Nomenclature")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION "Chemical compound visualization app")
set(CPACK_PACKAGE_CONTACT "Your Name <you@example.com>")
set(CPACK_GENERATOR "ZIP;TGZ")  # ZIP for Windows/macOS, TGZ for Linux