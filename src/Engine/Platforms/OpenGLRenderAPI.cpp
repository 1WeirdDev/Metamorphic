#include "mmafx.h"

#include "Metamorphic/Logger.h"

#include "Metamorphic/Rendering/RenderAPIS/OpenGLRenderAPI.h"

namespace Metamorphic{
    RenderAPI* RenderAPI::CreateRenderAPI(Application& app){
        return new OpenGLRenderAPI(app);
    }
    OpenGLRenderAPI::OpenGLRenderAPI(Application& app) : RenderAPI(app){}
    OpenGLRenderAPI::~OpenGLRenderAPI(){}

    void OpenGLRenderAPI::Init(){
        glClearColor(0.5, 0.5, 0.5, 1.0);
        MORPHIC_CORE_INFO("Initialized OpenGLRenderAPI");
    }

    void OpenGLRenderAPI::Shutdown(){
        MORPHIC_CORE_INFO("Shut Down OpenGLRenderAPI");
    }
    
    void OpenGLRenderAPI::OnWindowResize(WindowResizedEvent& e){
        glViewport(0, 0, e.GetWidth(), e.GetHeight());
        MORPHIC_CORE_INFO("OpenGLRenderAPI Resized window {0} {1}", e.GetWidth(), e.GetHeight());
    }
    void OpenGLRenderAPI::ClearScreen(){
        glClear(GL_COLOR_BUFFER_BIT);
    }
}