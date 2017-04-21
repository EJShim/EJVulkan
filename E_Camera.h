#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class E_Camera{
public:
    E_Camera();
    ~E_Camera();

protected:
    void Initialize();

public:
    void Update();

    glm::mat4 GetViewTransform(){return m_transform;}
    glm::mat4 GetProjectionTransform(){return m_projection;}

    void SetViewTransform( glm::mat4 trans ){m_transform = trans;}
    void SetProjectionTransform(glm::mat4 trans){m_projection = trans;}

    uint32_t GetWidth(){return m_viewWidth;}
    uint32_t GetHeight(){return m_viewHeight;}


protected:
    uint32_t m_viewWidth = 1000;
    uint32_t m_viewHeight = 800;

    glm::mat4 m_transform;
    glm::mat4 m_projection;
};
