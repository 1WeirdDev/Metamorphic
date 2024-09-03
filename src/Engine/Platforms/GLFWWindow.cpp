#include "mmafx.h"
#include "Metamorphic/Core.h"

#include "Metamorphic/Display/GLFWWindow.h"
#include "Metamorphic/Events/ApplicationEvents.h"
#include "Metamorphic/Events/InputEvents.h"
#include "Metamorphic/Logger.h"

namespace Metamorphic{
    Window* Window::Create(){
        return (Window*)new GLFWWindow();
    }
    GLFWWindow::GLFWWindow(){}
    GLFWWindow::~GLFWWindow(){}
    
    void GLFWWindow::Init(){
        if(!glfwInit()){
            MORPHIC_CORE_ERROR("Failed to initialize glfw.");
            return;
        }
        #ifdef METAMORPHIC_USE_VULKAN
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        #endif
        m_Window = glfwCreateWindow(m_Data.m_Width, m_Data.m_Height, "Metamorphic Engine", nullptr, nullptr);

        GLFWvidmode* videoMode = (GLFWvidmode*)glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowPos(m_Window, (videoMode->width - m_Data.m_Width) / 2, (videoMode->height - m_Data.m_Height) / 2);
        if(m_Window == nullptr){
            MORPHIC_CORE_ERROR("Failed to create window");
            std::exit(-1);
        }
        glfwMakeContextCurrent(m_Window);
        #ifdef METAMORPHIC_USE_OPENGL
        if(glewInit() != GLEW_OK){
            MORPHIC_CORE_ERROR("Glew failed to initialize");
            glfwTerminate();
            std::exit(-1);
            return;
        }
        #endif
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
    void GLFWWindow::Shutdown(){
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        MORPHIC_CORE_INFO("Destroyed window\n");
    }
    void GLFWWindow::Update(){
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void GLFWWindow::SetVsyncEnabled(bool p_Value){
        m_Data.m_VsyncEnabled = p_Value;

        glfwSwapInterval(p_Value ? 1 : 0);
    }
}