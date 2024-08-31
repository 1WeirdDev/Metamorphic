#include "mmepch.h"

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#define METAMORPHIC_NO_ENTRY_POINT
#include "Metamorphic.h"

using namespace Metamorphic;
int main(int argc, char** argv){
    Metamorphic::Logger::Init();

    if(!glfwInit()){
        MORPHIC_CORE_ERROR("Failed to initialize glfw\n");
        return -1;
    }
    GLFWwindow* glfw_window = glfwCreateWindow(1280, 720, "Metamorphic Editor", nullptr, nullptr);

    if(!glfw_window){
        MORPHIC_CORE_ERROR("Failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(glfw_window);
    MORPHIC_CORE_LOG("Initializing Editor");

    Window m;
    m.Init();
    Application* app = new Application();

    while(glfwWindowShouldClose(glfw_window) == false){
        
    }

    delete app;
    MORPHIC_INFO("Shutting down editor");
    glfwDestroyWindow(glfw_window);
    glfwTerminate();
}