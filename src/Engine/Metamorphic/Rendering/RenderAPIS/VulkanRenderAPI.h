#pragma once

#include "../RenderAPI.h"
namespace Metamorphic{
    class MORPHIC_API VulkanRenderAPI : public RenderAPI{
    public:
        VulkanRenderAPI(Application& p_app);
        ~VulkanRenderAPI() override;

        void Init() override;
        void Shutdown() override;

        void ClearScreen() override;
    private:
        VkInstance m_Instance;
        VkSurfaceKHR m_Surface;
    };
}