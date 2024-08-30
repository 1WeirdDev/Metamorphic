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
        input.Init();
    }
    Application::~Application(){
        input.Shutdown();
        m_Window.Shutdown();
    }
    
    void Application::Awake(){}
    void Application::Update(){
        m_Window.Update();
        input.Update();
    }
    void Application::LateUpdate(){}
    void Application::Draw(){}
}