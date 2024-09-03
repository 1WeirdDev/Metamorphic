#include "mmafx.h"

#include "Metamorphic/Logger.h"
#include "Metamorphic/Display/Rendering/VulkanRenderAPI.h"

namespace Metamorphic{
    RenderAPI* RenderAPI::CreateRenderAPI(){
        return new VulkanRenderAPI();
    }
    VulkanRenderAPI::VulkanRenderAPI(){}
    VulkanRenderAPI::~VulkanRenderAPI(){}
    
    void VulkanRenderAPI::Init(){
        /*MORPHIC_CORE_DEBUG("TEST1");
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        MORPHIC_CORE_DEBUG("TEST2");

        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        MORPHIC_CORE_DEBUG("TEST3");
        
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            MORPHIC_CORE_ERROR("Failed to initialize Vulkan RenderAPI");
            return;
        }*/
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        VkInstance instance = {};
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    throw std::runtime_error("failed to create instance!");
}

        MORPHIC_CORE_INFO("Initialized Vulkan RenderAPI");
    }
    void VulkanRenderAPI::Shutdown(){
        MORPHIC_CORE_INFO("Shutdown Vulkan RenderAPI");
    }

    void VulkanRenderAPI::ClearScreen(){}
}