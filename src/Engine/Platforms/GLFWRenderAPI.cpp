#include "mmafx.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Metamorphic/Logger.h"

#include "Metamorphic/Display/Rendering/RenderAPI.h"

namespace Metamorphic{
    RenderAPI::RenderAPI(){}
    RenderAPI::~RenderAPI(){}

    void RenderAPI::Init(){
        glClearColor(0.5, 0.5, 0.5, 1.0);
        MORPHIC_CORE_INFO("Initialized GLFW RenderAPI");
    }

    void RenderAPI::Shutdown(){
        MORPHIC_CORE_INFO("Shut Down GLFW RenderAPI");
    }
    void RenderAPI::ClearScreen(){
        glClear(GL_COLOR_BUFFER_BIT);
    }
}