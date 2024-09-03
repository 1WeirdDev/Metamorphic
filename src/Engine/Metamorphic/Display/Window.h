#pragma once
#include "mmafx.h"
#include "../Core.h"
#include "../Events/Event.h"

/*
#if METAMORPHIC_ENGINE_BUILD || METAMORPHIC_EDITOR_BUILD
    #if METAMORPHIC_USE_OPENGL
        #include <GL/glew.h>
        #include <GLFW/glfw3.h>
        #define WINDOW_TYPE GLFWwindow*
    #elif METAMORPHIC_USE_DIRECTX
        #define WINDOW_TYPE void*
    #else
        #error Invalid Rendering API Specified
    #endif
#else
#define WINDOW_TYPE void*
#endif
*/
namespace Metamorphic{
    class MORPHIC_API Window{
    public:
        static Window* Create();
        using EventHandlerCallback = std::function<void(Event&)>;

        struct WindowData{
            int m_Width = 1280;
            int m_Height = 720;
            bool m_VsyncEnabled = false;
            EventHandlerCallback m_EventCallback;
        };

        Window(){};
        virtual ~Window(){}
        
        virtual void Init(){}
        virtual void Shutdown(){}
        virtual void Update(){}

        virtual void SetVsyncEnabled(bool p_Value){}

        void SetEventHandlerCallback(EventHandlerCallback p_EventHandler){
            m_Data.m_EventCallback = p_EventHandler;
        }

        void SetShouldUpdate(bool p_Open) {m_IsOpen = p_Open;}

        inline int GetWidth() const {return m_Data.m_Width;}
        inline int GetHeight() const {return m_Data.m_Height;}
        inline bool ShouldUpdate() const {return m_IsOpen;}
    protected:
        //WINDOW_TYPE m_Window = nullptr;
        WindowData m_Data;
        bool m_IsOpen = false;
    };
}