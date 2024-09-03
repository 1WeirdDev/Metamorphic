#include "mmafx.h"

#include "Metamorphic/Logger.h"

#include "Metamorphic/Display/Rendering/OpenGLRenderAPI.h"

namespace Metamorphic{
    RenderAPI* RenderAPI::CreateRenderAPI(){
        return new OpenGLRenderAPI();
    }
    OpenGLRenderAPI::OpenGLRenderAPI(){}
    OpenGLRenderAPI::~OpenGLRenderAPI(){}

    void OpenGLRenderAPI::Init(){
        glClearColor(0.5, 0.5, 0.5, 1.0);
        MORPHIC_CORE_INFO("Initialized OpenGLRenderAPI");
    }

    void OpenGLRenderAPI::Shutdown(){
        MORPHIC_CORE_INFO("Shut Down OpenGLRenderAPI");
    }
    void OpenGLRenderAPI::ClearScreen(){
        glClear(GL_COLOR_BUFFER_BIT);
    }
}