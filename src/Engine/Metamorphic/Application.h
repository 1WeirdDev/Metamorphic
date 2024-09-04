#pragma once

#include "Core.h"
#include "Display/Window.h"
#include "Rendering/RenderAPI.h"
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
        void Shutdown();

        virtual void OnShutdown(){}
        virtual void OnAwake(){}
        virtual void OnUpdate(){}
        virtual void OnDraw(){}
    public:
        bool ShouldUpdate() const noexcept {return m_Window->ShouldUpdate();}
        Window* GetWindow() const noexcept {return m_Window;}
        RenderAPI* GetRenderAPI() const noexcept{return m_RenderAPI;}

        const Input& GetInput() const noexcept {return m_Input;}
        const SceneManager& GetSceneManager() const noexcept {return m_SceneManager;}
    protected:
        Window* m_Window = nullptr;
        RenderAPI* m_RenderAPI = nullptr;
        Input m_Input;
        SceneManager m_SceneManager;
    };
}