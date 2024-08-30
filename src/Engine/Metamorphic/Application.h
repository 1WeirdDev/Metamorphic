#pragma once

#include "Core.h"
#include "Display/Window.h"
#include "Input.h"

namespace Metamorphic{
    class MORPHIC_API Application{
    public:
        static Application* CreateSandbox();

        Application();
        virtual ~Application();

        virtual void Awake();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Draw();
    public:
        bool ShouldUpdate() const {return m_Window.ShouldUpdate();}
        const Window& GetWindow() const{return m_Window;}
        const Input& GetInput() const {return input;}
    protected:
        Window m_Window;
        Input input;
    };
}