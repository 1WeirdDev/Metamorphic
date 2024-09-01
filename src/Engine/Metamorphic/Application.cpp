#include "mmafx.h"
#include "Application.h"

#include "Events/ApplicationEvents.h"
#include "Events/InputEvents.h"
#include "Logger.h"

namespace Metamorphic{
    Application::Application(){
        m_Window.Init();

        m_Window.SetEventHandlerCallback([this](Event& e){
            EventDispatcher dispatcher(e);
            dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& event){
                m_Window.SetShouldUpdate(false);
                return true;
            });

            dispatcher.Dispatch<KeyDownEvent>([this](KeyDownEvent& event){
                std::string s = "key down" + std::to_string(event.GetKey()) + std::string(" \n");
                MORPHIC_CORE_LOG(s.c_str());
                return true;
            });
            dispatcher.Dispatch<KeyUpEvent>([this](KeyUpEvent& event){
                std::string s = "key up" + std::to_string(event.GetKey()) + std::string(" \n");
                MORPHIC_CORE_LOG(s.c_str());
                return true;
            });

            dispatcher.Dispatch<WindowResizedEvent>([this](WindowResizedEvent& event){
                MORPHIC_CORE_LOG("Window resized {0} {1}", event.GetWidth(), event.GetHeight());
                return true;
            });
        });

        //Init Input System
        m_Input.Init();

        //Init scenes
        m_SceneManager.Init();
    }
    Application::~Application(){
    }
    
    void Application::Awake(){
        OnAwake();
    }
    void Application::Update(){
        m_Window.Update();
        m_Input.Update();
        
        m_SceneManager.Update();
        OnUpdate();
    }
    void Application::Draw(){
        m_SceneManager.Draw();
        OnDraw();
    }

    void Application::CleanUp(){
        m_SceneManager.Shutdown();
        m_Input.Shutdown();
        m_Window.Shutdown();
    }
}