#include "E_Camera.h"
#include <iostream>

E_Camera::E_Camera()
{
    Initialize();
}

E_Camera::~E_Camera()
{

}



void E_Camera::Initialize()
{
    m_transform = glm::lookAt(glm::vec3(15.0f, 15.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_projection = glm::perspective(glm::radians(45.0f), m_viewWidth / (float) m_viewHeight, 0.1f, 500.0f);
}
