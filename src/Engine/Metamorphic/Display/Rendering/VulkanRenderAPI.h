#pragma once

#include "RenderAPI.h"
namespace Metamorphic{
    class MORPHIC_API VulkanRenderAPI : public RenderAPI{
    public:
        VulkanRenderAPI();
        ~VulkanRenderAPI() override;

        void Init() override;
        void Shutdown() override;

        void ClearScreen() override;
    private:
        //VkApplicationInfo appInfo{};
        //VkInstanceCreateInfo createInfo{};

        //VkInstance instance;
    };
}