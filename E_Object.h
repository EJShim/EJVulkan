#pragma once

#include "E_Struct.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class E_Object{
public:
    E_Object();
    ~E_Object();


public:
    void Update();

    std::vector<E_VAO> GetVertexArray(){return m_vertices;}
    std::vector<uint16_t> GetIndexArray(){return m_indices;}
    glm::mat4 GetTransform(){return m_transform;}
    void SetTransform(glm::mat4 trans){m_transform = trans;}

protected:
    const std::vector<E_VAO> m_vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}
    };

    const std::vector<uint16_t> m_indices = {
        0,1,2,2,3,0
    };


    //Model Matrix
    glm::mat4 m_transform;
};
