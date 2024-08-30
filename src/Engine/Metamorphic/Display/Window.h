#pragma once
#include "mmafx.h"
#include "../Core.h"
#include "../Events/Event.h"

#ifdef METAMORPHIC_ENGINE_BUILD
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define WINDOW_TYPE GLFWwindow*
#else
#define WINDOW_TYPE void*
#endif

namespace Metamorphic{
    class MORPHIC_API Window{
    public:
        using EventHandlerCallback = std::function<void(Event&)>;

        struct WindowData{
            int m_Width = 1280;
            int m_Height = 720;
            EventHandlerCallback m_EventCallback;
        };
        
        void Init();
        void Shutdown();

        void Update();

        void SetEventHandlerCallback(EventHandlerCallback p_EventHandler);

        void SetShouldUpdate(bool p_Open) {m_IsOpen = p_Open;}
        bool ShouldUpdate() const {return m_IsOpen;}
    private:
        WINDOW_TYPE m_Window = nullptr;
        bool m_IsOpen;
        WindowData m_Data;
    };
}