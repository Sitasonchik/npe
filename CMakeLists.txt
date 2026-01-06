cmake_minimum_required(VERSION 3.10.0)
project(npe VERSION 0.1.0 LANGUAGES C CXX)



find_package(OpenSSL REQUIRED)
# find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
# find_package(GLEW REQUIRED)

add_subdirectory(imgui)


add_executable(npe src/main.cpp)
set(CMAKE_CXX_STANDARD 17)

target_link_libraries(npe OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(npe OpenGL::GL glfw dl imgui)


