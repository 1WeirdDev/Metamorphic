#include "mmafx.h"

#include "Metamorphic/Logger.h"
#include "Metamorphic/Rendering/RenderAPIS/DirectXRenderAPI.h"

namespace Metamorphic{
    RenderAPI* RenderAPI::CreateRenderAPI(Application& app){
        return new DirectXRenderAPI(app);
    }

    DirectXRenderAPI::DirectXRenderAPI(Application& app) : RenderAPI(app){}
    DirectXRenderAPI::~DirectXRenderAPI(){}

    void DirectXRenderAPI::Init(){
        MORPHIC_CORE_INFO("Initialized DirectXRenderAPI");
    }
    void DirectXRenderAPI::Shutdown(){
        MORPHIC_CORE_INFO("Shutdown DirectXRenderAPI");
    }

    void DirectXRenderAPI::ClearScreen(){}
}