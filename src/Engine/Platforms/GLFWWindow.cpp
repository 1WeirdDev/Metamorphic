#include "mmafx.h"
#include "Metamorphic/Core.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Metamorphic/Display/Window.h"
#include "Metamorphic/Events/ApplicationEvents.h"
#include "Metamorphic/Events/InputEvents.h"
#include "Metamorphic/Logger.h"

namespace Metamorphic{

    void Window::Init(){
        if(!glfwInit()){
            MORPHIC_CORE_ERROR("Failed to initialize glfw.");
            return;
        }

        int width = 1280;
        int height = 720;
        m_Window = glfwCreateWindow(width, height, "Metamorphic Engine", nullptr, nullptr);

        GLFWvidmode* videoMode = (GLFWvidmode*)glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowPos(m_Window, (videoMode->width - width) / 2, (videoMode->height - height) / 2);
        if(m_Window == nullptr){
            MORPHIC_CORE_ERROR("Failed to create window");
            std::exit(-1);
        }
        glfwMakeContextCurrent(m_Window);
        if(glewInit() != GLEW_OK){
            MORPHIC_CORE_ERROR("Glew failed to initialize");
            glfwTerminate();
            std::exit(-1);
            return;
        }
		glfwSetWindowUserPointer(m_Window, &m_Data);

        //Setting callback
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
            WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            window_data.m_EventCallback(event);
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
            WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window);
            window_data.m_Width = width;
            window_data.m_Height = height;

            //TODO: May have custom viewport inside the editor
            glViewport(0,0, width, height);
            WindowResizedEvent event(width, height);
            window_data.m_EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
            WindowData& window_data = *(WindowData*)glfwGetWindowUserPointer(window);
            if(action == GLFW_RELEASE){
                KeyUpEvent event(key, mods);
                window_data.m_EventCallback(event);
                return;
            }
            KeyDownEvent event(key, mods, action == GLFW_REPEAT);
            window_data.m_EventCallback(event);
        });
        m_IsOpen = true;
        MORPHIC_CORE_INFO("Created window\n");
    }
    void Window::Shutdown(){
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        MORPHIC_CORE_INFO("Destroyed window\n");
    }
    void Window::SetEventHandlerCallback(EventHandlerCallback p_EventHandler){
        m_Data.m_EventCallback = p_EventHandler;
    }
    void Window::Update(){
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}