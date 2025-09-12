file(GLOB NATIVEFILEDIALOGSOURCES "*.cpp" "*.c")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_library(nativefiledialog STATIC ${NATIVEFILEDIALOGSOURCES})

target_include_directories(nativefiledialog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(nativefiledialog PRIVATE ${GTK3_INCLUDE_DIRS})
target_link_libraries(nativefiledialog PRIVATE ${GTK3_LIBRARIES})
target_compile_options(nativefiledialog PRIVATE ${GTK3_CFLAGS_OTHER})

