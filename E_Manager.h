#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include "VDeleter.hpp"

#include <vector>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>



class E_Manager{
private:
    static const int WIDTH = 1000;
    static const int HEIGHT = 800;

    struct Vertex{
        glm::vec2 pos;
        glm::vec3 color;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription = {};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
           std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

           attributeDescriptions[0].binding = 0;
           attributeDescriptions[0].location = 0;
           attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
           attributeDescriptions[0].offset = offsetof(Vertex, pos);

           attributeDescriptions[1].binding = 0;
           attributeDescriptions[1].location = 1;
           attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
           attributeDescriptions[1].offset = offsetof(Vertex, color);

           return attributeDescriptions;
       }
    };


    struct QueueFamilyIndices
    {
        int graphicsFamily = -1;
        int presentFamily = -1;

        bool isComplete() {
            return graphicsFamily >= 0 && presentFamily >= 0;
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };


    #ifdef NDEBUG
    const bool enableValidationLayers = false;
    #else
    const bool enableValidationLayers = true;
    #endif

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
    {
        std::cerr << "validation layer: " << msg << std::endl;

        return VK_FALSE;
    }



public:
    E_Manager();
    ~E_Manager();

protected:
    void Initialize();


    ///Init GLFW
    void InitWindow();

    ///Initialize Vulkan
    void InitVulkan();
    void CreateInstance();
    void SetUpDebugCallback();
    void CreateSurface();
    void PickPhysicalDevice();
    void CreateLogicalDevice();
    void CreateSwapChain();
    void CreateImageViews();
    void CreateRenderPass();

    void CreateDescriptorSetLayout();
    void CreateGraphicsPipeLine();
    void CreateFrameBuffers();
    void CreateCommandPool();

    void CreateVertexBuffer();
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VDeleter<VkBuffer>& buffer, VDeleter<VkDeviceMemory>& bufferMemory);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void CreateIndexBuffer();
    void CreateUniformBuffer();
    void CreateDescriptorPool();
    void CreateDescriptorSet();

    void CreateCommandBuffers();
    void CreateSemaphores();



    void UpdateUniformBuffer();
    void MainLoop();

protected:
    static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);

    std::vector<const char*> GetRequiredExtensions();
    void DrawFrame();

    bool IsDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);

    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    static std::vector<char> ReadFile(const std::string& filename);
    void CreateShaderModule(const std::vector<char>& code, VDeleter<VkShaderModule>& shaderModule);
protected:
    GLFWwindow* window;

    VDeleter<VkInstance> instance{vkDestroyInstance};
    VDeleter<VkDebugReportCallbackEXT> callback{instance, DestroyDebugReportCallbackEXT};
    VDeleter<VkSurfaceKHR> surface{instance, vkDestroySurfaceKHR};


    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VDeleter<VkDevice> device{vkDestroyDevice};

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VDeleter<VkSwapchainKHR> swapChain{device, vkDestroySwapchainKHR};
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VDeleter<VkImageView>> swapChainImageViews;
    std::vector<VDeleter<VkFramebuffer>> swapChainFramebuffers;

    VDeleter<VkRenderPass> renderPass{device, vkDestroyRenderPass};
    VDeleter<VkPipelineLayout> pipelineLayout{device, vkDestroyPipelineLayout};
    VDeleter<VkPipeline> graphicsPipeline{device, vkDestroyPipeline};

    VDeleter<VkCommandPool> commandPool{device, vkDestroyCommandPool};
    std::vector<VkCommandBuffer> commandBuffers;

    VDeleter<VkSemaphore> imageAvailableSemaphore{device, vkDestroySemaphore};
    VDeleter<VkSemaphore> renderFinishedSemaphore{device, vkDestroySemaphore};



public:
    //Vertices and Indices Data


    const std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.5f, 1.0f}}
    };


    const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0
    };


    //Vertex Buffer Data
    VDeleter<VkBuffer> vertexBuffer{device, vkDestroyBuffer};
    VDeleter<VkDeviceMemory> vertexBufferMemory{device, vkFreeMemory};
    VDeleter<VkBuffer> indexBuffer{device, vkDestroyBuffer};
    VDeleter<VkDeviceMemory> indexBufferMemory{device, vkFreeMemory};

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);


public:
    //Description Set
    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
        float time;
    };

    VDeleter<VkDescriptorSetLayout> descriptorSetLayout{device, vkDestroyDescriptorSetLayout};
    VDeleter<VkBuffer> uniformStagingBuffer{device, vkDestroyBuffer};
    VDeleter<VkDeviceMemory> uniformStagingBufferMemory{device, vkFreeMemory};
    VDeleter<VkBuffer> uniformBuffer{device, vkDestroyBuffer};
    VDeleter<VkDeviceMemory> uniformBufferMemory{device, vkFreeMemory};

    VDeleter<VkDescriptorPool> descriptorPool{device, vkDestroyDescriptorPool};
    VkDescriptorSet descriptorSet;
};
