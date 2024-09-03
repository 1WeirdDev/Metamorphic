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
    private:
        class GLFWwindow* m_Window = nullptr;
    };
}