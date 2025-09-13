cmake_minimum_required(VERSION 3.20)
project(ChemCraft)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(GLOB SOURCES "src/*.cpp" "src/chemistry/*.cpp" "src/graphics/*.cpp" "src/render/*.cpp" "src/UI/*.cpp" "src/management/*.cpp" "src/objects/*.cpp")

# find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/imgui)
add_subdirectory(lib/nativefiledialog)
add_subdirectory(lib/stb_image)
add_subdirectory(lib/json)
add_subdirectory(lib/glm)

add_executable(ChemCraft ${SOURCES})

target_link_libraries(ChemCraft PUBLIC glfw)
target_link_libraries(ChemCraft PUBLIC OpenGL::GL)
target_link_libraries(ChemCraft PUBLIC glad)

target_link_libraries(ChemCraft PRIVATE imgui)
target_link_libraries(ChemCraft PRIVATE nativefiledialog)
target_link_libraries(ChemCraft PRIVATE stb_image)
target_link_libraries(ChemCraft PRIVATE json)
target_link_libraries(ChemCraft PRIVATE glm)

target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/chemistry)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/UI)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/render)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/graphics)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/management)
target_include_directories(ChemCraft PRIVATE ${CMAKE_SOURCE_DIR}/include/objects)

#Copying assets cause sometimes the binary goes insdie another folder
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})    
file(COPY ${CMAKE_SOURCE_DIR}/config DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
endif()

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION .)

include(CPack)

set(CPACK_PACKAGE_NAME "ChemCraft")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "Chemical compounds visualization app")
set(CPACK_PACKAGE_CONTACT "Antasma-X <rayyansohaibali@gmail.com>")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

# -----------------------------
# Platform-specific packaging
# -----------------------------
if(WIN32)
    # Windows installer using NSIS
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_DISPLAY_NAME "MyCppApp")
    set(CPACK_NSIS_PACKAGE_NAME "MyCppApp Installer")
    set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\MyCppApp.exe")
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/assets/app_icon.ico")  # optional
    set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/assets/app_icon.ico") # optional
    set(CPACK_NSIS_CREATE_DESKTOP_LINK ON)
elseif(APPLE)
    # macOS .dmg or tar.gz
    set(CPACK_GENERATOR "DragNDrop;TGZ")
elseif(UNIX)
    # Linux .tar.gz or .deb/.rpm
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
endif()