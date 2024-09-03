#include "mmafx.h"

#include "Metamorphic/Logger.h"
#include "Metamorphic/Display/Rendering/RenderAPI.h"

namespace Metamorphic{
    RenderAPI::RenderAPI(){}
    RenderAPI::~RenderAPI(){}

    void RenderAPI::Init(){
        MORPHIC_CORE_INFO("Initialized DirectX RenderAPI");
    }
    void RenderAPI::Shutdown(){
        MORPHIC_CORE_INFO("Shutdown DirectX RenderAPI");
    }

    void RenderAPI::ClearScreen(){}
}