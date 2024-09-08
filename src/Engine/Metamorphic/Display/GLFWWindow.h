#pragma once

#include "Window.h"

namespace Metamorphic{
    class GLFWWindow : public Window{
    public:
        GLFWWindow();
        ~GLFWWindow();

        void Init() override;
        void Shutdown() override;

        void SetVsyncEnabled(bool p_Value);
        void Update() override;

    public:
    #if METAMORPHIC_PLATFORM == Windows && METAMORPHIC_EXPOSE_GLFW_NATIVE
        HWND GetHWND() const{
            return glfwGetWin32Window(m_Window);
        }
    #endif

        GLFWwindow* GetGLFWWindow() const noexcept{return m_Window;}
    private:
       GLFWwindow* m_Window = nullptr;
    };
}