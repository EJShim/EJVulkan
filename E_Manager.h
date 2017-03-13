#pragma once

#include <GLFW/glfw3.h>

class E_Manager{
public:
    E_Manager();
    ~E_Manager();

protected:
    void Initialize();

    void run();
    void initWindow();
    void initVulkan();
    void mainLoop();

private:
    GLFWwindow* m_window;

    VDeleter<VkInstance> instance{vkDestroyInstance};
    VDeleter<VkDebugReportCallbackEXT> callback{instance, DestroyDebugReportCallbackEXT};
    VDeleter<VkSurfaceKHR> surface{instance, vkDestroySurfaceKHR};
};
