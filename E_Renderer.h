#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "VDeleter.hpp"

#include "E_Camera.h"
#include "E_Object.h"

#include <vector>
#include "E_Struct.hpp"

class E_Renderer{
public:
    E_Renderer();
    ~E_Renderer();

private:
    void Initialize();

protected:
    E_Camera* m_camera;
    std::vector<E_Object*> m_objectList;

protected:

    //Const Vals
    #ifdef NDEBUG
    const bool enableValidationLayers = false;
    #else
    const bool enableValidationLayers = true;
    #endif

    //Initialziae Variables
    uint32_t WIDTH = 1000;
    uint32_t HEIGHT = 800;
    const std::vector<const char*> m_validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    //Debug Callback
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
    {
        std::cerr << "validation layer: " << msg << std::endl;

        return VK_FALSE;
    }

    //Device Extensions
    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };



protected:
    //Surface
    GLFWwindow* m_window;

    //Instance
    VDeleter<VkInstance> m_instance{vkDestroyInstance};

    //Surface
    VDeleter<VkSurfaceKHR> m_surface{m_instance, vkDestroySurfaceKHR};


    //Physical Device
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VDeleter<VkDevice> m_logicalDevice{vkDestroyDevice};
    //Queuue
    VkQueue m_graphicsQueue;
    VkQueue m_presentQueue;

    //SwapChain
    VDeleter<VkSwapchainKHR> m_swapChain{m_logicalDevice, vkDestroySwapchainKHR};
    std::vector<VkImage> m_swapChainImages;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;


    //Image Frame
    std::vector<VDeleter<VkImageView>> m_swapChainImageViews;
    std::vector<VDeleter<VkFramebuffer>> m_swapChainFramebuffers;

    //Render Pass
    VDeleter<VkRenderPass> m_renderPass{m_logicalDevice, vkDestroyRenderPass};

    //Descriptor SetUpDebugCallback
    VDeleter<VkDescriptorSetLayout> m_descriptorSetLayout{m_logicalDevice, vkDestroyDescriptorSetLayout};

    //Pipeline layout
    VDeleter<VkPipelineLayout> m_pipelineLayout{m_logicalDevice, vkDestroyPipelineLayout};
    VDeleter<VkPipeline> m_graphicsPipeline{m_logicalDevice, vkDestroyPipeline};

    //Command pool
    VDeleter<VkCommandPool> m_commandPool{m_logicalDevice, vkDestroyCommandPool};
    std::vector<VkCommandBuffer> m_commandBuffers;


    //Vertex Buffer
    VDeleter<VkBuffer> m_vertexBuffer{m_logicalDevice, vkDestroyBuffer};
    VDeleter<VkDeviceMemory> m_vertexBufferMemory{m_logicalDevice, vkFreeMemory};
    VDeleter<VkBuffer> m_indexBuffer{m_logicalDevice, vkDestroyBuffer};
    VDeleter<VkDeviceMemory> m_indexBufferMemory{m_logicalDevice, vkFreeMemory};

    //Uniform Buffer
    VDeleter<VkBuffer> m_uniformStagingBuffer{m_logicalDevice, vkDestroyBuffer};
    VDeleter<VkDeviceMemory> m_uniformStagingBufferMemory{m_logicalDevice, vkFreeMemory};
    VDeleter<VkBuffer> m_uniformBuffer{m_logicalDevice, vkDestroyBuffer};
    VDeleter<VkDeviceMemory> m_uniformBufferMemory{m_logicalDevice, vkFreeMemory};
    E_UBO m_ubo;


    //Descriptor pool
    VDeleter<VkDescriptorPool> m_descriptorPool{m_logicalDevice, vkDestroyDescriptorPool};
    VkDescriptorSet m_descriptorSet;


    //Semaphore
    VDeleter<VkSemaphore> m_imageAvailableSemaphore{m_logicalDevice, vkDestroySemaphore};
    VDeleter<VkSemaphore> m_renderFinishedSemaphore{m_logicalDevice, vkDestroySemaphore};


    ///Image View
    VDeleter<VkImage> m_depthImage{m_logicalDevice, vkDestroyImage};
    VDeleter<VkDeviceMemory> m_depthImageMemory{m_logicalDevice, vkFreeMemory};
    VDeleter<VkImageView> m_depthImageView{m_logicalDevice, vkDestroyImageView};

protected:
    //Initialize Functions
    void InitWindow();

    //Initialize Vulkan
    void CreateInstance();
    void SetUpDebugCallback();
    void CreateSurface();
    void PickPhysicalDevice();
    void CreateLogicalDevice();


    void CreateSwapChain();
    void CreateImageViews();
    void CreateRenderPass();

    //Set Number of Descriptor Set Here!
    void CreateDescriptorSetLayout();
    void CreateGraphicsPipeLine();
    void CreateFrameBuffers();
    void CreateCommandPool();

    void CreateDepthResource();


    void UpdateState();

    ////Create Vertex and Uniform Buffer
    void CreateVertexBuffer();
    void CreateIndexBuffer();
    void CreateUniformBuffer();


    void CreateDescriptorPool();
    void CreateDescriptorSet();

    void CreateCommandBuffers();
    void CreateSemaphores();

    void UpdateUniform();
    void DrawFrame();


protected:
    //Module Functions
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

    // Physical Device
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    //Swap Chain
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);


    //Create Shader Module
    static std::vector<char> ReadFile(const std::string& filename);
    void CreateShaderModule(const std::vector<char>& code, VDeleter<VkShaderModule>& shaderModule);


    //Create and Copy Buffer
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VDeleter<VkBuffer>& buffer, VDeleter<VkDeviceMemory>& bufferMemory);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);


    //Depth
    void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VDeleter<VkImage>& image, VDeleter<VkDeviceMemory>& imageMemory);

    void CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VDeleter<VkImageView>& imageView);

    VkFormat FindDepthFormat();
    VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    VkCommandBuffer BeginSingleTimeCommands();
    void EndSingleTimeCommands(VkCommandBuffer commandBuffer);




public:
    GLFWwindow* GetWindow(){return m_window;}
    VDeleter<VkDevice> GetDevice(){return m_logicalDevice;}

    //Caemra Functions
    void SetCamera(E_Camera* cam);
    E_Camera* GetCamera(){return m_camera;}

    void AddObject(E_Object* object);


    //Update And Render
    void Render();
};
