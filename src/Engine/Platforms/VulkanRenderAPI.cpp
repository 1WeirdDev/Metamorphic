#include "mmafx.h"

#include "Metamorphic/Logger.h"
#include "Metamorphic/Display/Rendering/VulkanRenderAPI.h"

namespace Metamorphic{
    RenderAPI* RenderAPI::CreateRenderAPI(){
        return new VulkanRenderAPI();
    }
    VulkanRenderAPI::VulkanRenderAPI(){
        MORPHIC_CORE_INFO("Initialized Vulkan RenderAPI");
    }
    VulkanRenderAPI::~VulkanRenderAPI(){
        MORPHIC_CORE_INFO("Shutdown Vulkan RenderAPI");
    }
    
    void VulkanRenderAPI::Init(){}
    void VulkanRenderAPI::Shutdown(){}

    void VulkanRenderAPI::ClearScreen(){}
}