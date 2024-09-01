#pragma once

#include "Core.h"
#include "Display/Window.h"
#include "Input.h"
#include "Scene/SceneManager.h"

namespace Metamorphic{
    class MORPHIC_API Application{
    public:
        static Application* CreateSandbox();

        Application();
        virtual ~Application();

        void Awake();
        void Update();
        void Draw();
        void CleanUp();

        virtual void OnAwake(){}
        virtual void OnUpdate(){}
        virtual void OnDraw(){}
    public:
        bool ShouldUpdate() const noexcept {return m_Window.ShouldUpdate();}
        const Window& GetWindow() const noexcept {return m_Window;}
        const Input& GetInput() const noexcept {return m_Input;}
        const SceneManager& GetSceneManager() const noexcept {return m_SceneManager;}
    protected:
        Window m_Window;
        Input m_Input;
        SceneManager m_SceneManager;
    };
}