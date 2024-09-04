#include "mmafx.h"

#include "Metamorphic/Logger.h"
#include "Metamorphic/Rendering/RenderAPIS/DirectXRenderAPI.h"

namespace Metamorphic{
    RenderAPI* RenderAPI::CreateRenderAPI(){
        return new DirectXRenderAPI();
    }

    DirectXRenderAPI::DirectXRenderAPI(){}
    DirectXRenderAPI::~DirectXRenderAPI(){}

    void DirectXRenderAPI::Init(){
        MORPHIC_CORE_INFO("Initialized DirectXRenderAPI");
    }
    void DirectXRenderAPI::Shutdown(){
        MORPHIC_CORE_INFO("Shutdown DirectXRenderAPI");
    }

    void DirectXRenderAPI::ClearScreen(){}
}