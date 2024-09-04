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

        uint32_t extensionCount = 0;
        const char** extensions = glfwGetRequiredInstanceExtensions(&extensionCount);
        if (!extensions) {
            MORPHIC_CORE_ERROR("Failed to get required Vulkan extensions for RenderAPI");
            glfwTerminate();
            return;
        }

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        createInfo.enabledExtensionCount = extensionCount;
        createInfo.ppEnabledExtensionNames = extensions;
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
            MORPHIC_CORE_ERROR("Failed To Initialize Vulkan RenderAPI");
            return;
        }

        //Create Surface
        VkResult result = {};
        #ifdef METAMORPHIC_USE_GLFW
        result = glfwCreateWindowSurface(m_Instance, ((GLFWWindow*)m_Application->GetWindow())->GetGLFWWindow(), nullptr, &m_Surface);
        #endif
        switch (result) {
    case VK_ERROR_OUT_OF_HOST_MEMORY:
        std::cerr << "Out of host memory" << std::endl;
        break;
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
        std::cerr << "Out of device memory" << std::endl;
        break;
    case VK_ERROR_INITIALIZATION_FAILED:
        std::cerr << "Initialization failed" << std::endl;
        break;
    case VK_ERROR_EXTENSION_NOT_PRESENT:
        std::cerr << "Extension not present" << std::endl;
        break;
    case VK_ERROR_FEATURE_NOT_PRESENT:
        std::cerr << "Feature not present" << std::endl;
        break;
    case VK_ERROR_FORMAT_NOT_SUPPORTED:
        std::cerr << "Format not supported" << std::endl;
        break;
    case VK_ERROR_SURFACE_LOST_KHR:
        std::cerr << "Surface lost" << std::endl;
        break;
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        std::cerr << "Native window in use" << std::endl;
        break;
    default:
        std::cerr << "Unknown error " << result << std::endl;
        break;
}

        if (result != VK_SUCCESS) {
            MORPHIC_CORE_ERROR("Failed To Initialize Vulkan RenderAPI Surface View");
            return;
        }

        MORPHIC_CORE_INFO("Initialized Vulkan RenderAPI");
    }
    void VulkanRenderAPI::Shutdown(){
        vkDestroyInstance(m_Instance, nullptr);
        MORPHIC_CORE_INFO("Shutdown Vulkan RenderAPI");
    }

    void VulkanRenderAPI::ClearScreen(){}
}