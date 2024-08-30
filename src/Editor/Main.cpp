#include "mmepch.h"

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#define METAMORPHIC_NO_ENTRY_POINT
#include "Metamorphic.h"

int main(int argc, char** argv){
    if(!glfwInit()){
        printf("Failed to initialize glfw\n");
        return -1;
    }

    Metamorphic::Logger::Init();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Metamorphic Editor", nullptr, nullptr);

    if(!window){
        printf("Failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    MORPHIC_CORE_LOG("HELLO");
    while(glfwWindowShouldClose(window) == false){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    MORPHIC_INFO("Shutting down editor");
    glfwTerminate();
}