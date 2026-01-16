cmake_minimum_required(VERSION 3.10.0)
project(npe VERSION 0.1.0 LANGUAGES C CXX)



find_package(OpenSSL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)


add_library(imgui
    imgui_lib/imgui.cpp
    imgui_lib/imgui_demo.cpp
    imgui_lib/imgui_draw.cpp
    imgui_lib/imgui_tables.cpp
    imgui_lib/imgui_widgets.cpp
    imgui_lib/backends/imgui_impl_glfw.cpp
    imgui_lib/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui_lib/)

target_link_libraries(imgui PRIVATE OpenGL::GL glfw)

add_executable(npe src/main.cpp)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(npe OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(npe OpenGL::GL glfw dl imgui)


