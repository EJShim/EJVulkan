#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <vector>


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


struct E_VAO{
    glm::vec3 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription = {};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(E_VAO);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
       std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

       attributeDescriptions[0].binding = 0;
       attributeDescriptions[0].location = 0;
       attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
       attributeDescriptions[0].offset = offsetof(E_VAO, pos);

       attributeDescriptions[1].binding = 0;
       attributeDescriptions[1].location = 1;
       attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
       attributeDescriptions[1].offset = offsetof(E_VAO, color);

       return attributeDescriptions;
   }
};

struct E_UBO{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
    float time;
};
