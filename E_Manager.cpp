#include "E_Manager.h"

#include <GLFW/glfw3.h>
#include <iostream>

E_Manager::E_Manager()
{
    this->Initialize();
}

E_Manager::~E_Manager()
{

}

void E_Manager::Initialize()
{
    std::cout << "Manager Initialized" << std::endl;

    GLFWwindow* window;
}
