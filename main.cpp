#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <cstring>
#include <set>

///Include Manager
#include "E_Manager.h"


int main()
{
    E_Manager* Mgr = new E_Manager();

    // try {
    //     app.run();
    // } catch (const std::runtime_error& e) {
    //     std::cerr << e.what() << std::endl;
    //     return EXIT_FAILURE;
    // }

    return EXIT_SUCCESS;
}
