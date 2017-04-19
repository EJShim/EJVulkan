#include "E_Camera.h"
#include <iostream>

E_Camera::E_Camera()
{
    std::cout << "Camera Initialized" << std::endl;
}

E_Camera::~E_Camera()
{

}


void E_Camera::Update()
{
    std::cout << "Camera Update" << std::endl;
}
