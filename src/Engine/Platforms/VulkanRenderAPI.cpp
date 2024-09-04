#include "mmafx.h"

#include "Metamorphic/Logger.h"
#include "Metamorphic/Display/GLFWWindow.h"
#include "Metamorphic/Rendering/RenderAPIS/VulkanRenderAPI.h"
#include "Metamorphic/Application.h"

namespace Metamorphic{
    RenderAPI* RenderAPI::CreateRenderAPI(Application& p_App){
        return new VulkanRenderAPI(p_App);
    }
    VulkanRenderAPI::VulkanRenderAPI(Application& p_App) : RenderAPI(p_App){}
    VulkanRenderAPI::~VulkanRenderAPI(){}
    
    void VulkanRenderAPI::Init(){
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

        if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
            MORPHIC_CORE_ERROR("Failed To Initialize Vulkan RenderAPI");
            return;
        }

        //Create Surface
        VkResult result;
        #ifdef METAMORPHIC_USE_GLFW
        //HWND hwnd = ((GLFWWindow*)m_Application->GetWindow())->GetHWND();
        result = glfwCreateWindowSurface(m_Instance, ((GLFWWindow*)m_Application->GetWindow())->GetGLFWWindow(), nullptr, &m_Surface);
        #endif

        MORPHIC_CORE_INFO("Initialized Vulkan RenderAPI");
    }
    void VulkanRenderAPI::Shutdown(){
        vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
        vkDestroyInstance(m_Instance, nullptr);
        MORPHIC_CORE_INFO("Shutdown Vulkan RenderAPI");
    }

    void VulkanRenderAPI::ClearScreen(){}
}