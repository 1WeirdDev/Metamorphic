#pragma once

#include "mmafx.h"
#include "Metamorphic/Core.h"
#include "Metamorphic/Events/ApplicationEvents.h"

namespace Metamorphic{
    class Application;
    class MORPHIC_API RenderAPI{
    public:
        static RenderAPI* CreateRenderAPI(Application& application);

        RenderAPI(Application& p_App){m_Application = &p_App;}
        virtual ~RenderAPI(){}

        virtual void Init(){}
        virtual void Shutdown(){}

        virtual void OnWindowResize(WindowResizedEvent& e){}
        virtual void ClearScreen(){}
    protected:
        Application* m_Application = nullptr;
    };
}