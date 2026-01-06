#include "crypt.hpp"
#include "fs.hpp"
#include <cstddef>
#include "imgui.h"           
#include "backends/imgui_impl_glfw.h"  
#include "backends/imgui_impl_opengl3.h" 
#include <GLFW/glfw3.h>   

const size_t width = 300;
const size_t height = 300;

int main(){
    glfwInit();
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, "npe", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    int fb_width, fb_height;
    bool modec = 0;

    auto key = new char[1024]();
    auto file_name = new char[256]();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        glfwGetFramebufferSize(window, &fb_width, &fb_height);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)fb_width, (float)fb_height));
        ImGui::Begin("main", nullptr,
        ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoScrollbar 
        );


    ImGui::Text("file name:");
    ImGui::InputText("file name", file_name, 1024);
    ImGui::Text("key:");
    ImGui::InputText("key", key, 1024);
    if (ImGui::Button("choose mode")) {
        modec = !modec;
    }
    if(modec){
        ImGui::Text("decrypt");

    } else{
        ImGui::Text("encrypt");
    }
    if(ImGui::Button("do")){
        if(modec){       
            auto tmp_d = file_read(file_name);
            auto tmp_dec = AES128_DEC(reinterpret_cast<char *>(tmp_d.text), key, tmp_d.size);
            file_write(file_name, tmp_dec);

        } else{
            auto tmp_d = file_read(file_name);
            auto tmp_enc = AES128_ENC(reinterpret_cast<char *>(tmp_d.text), key, tmp_d.size);
            file_write(file_name, tmp_enc);

        }
    }
    ImGui::End();   

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    delete[] key;
    delete[] file_name;
    return 0;
}