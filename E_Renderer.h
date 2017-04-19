#pragma once

#include "E_Camera.h"

class E_Renderer{
public:
    E_Renderer();
    ~E_Renderer();

private:
    void Initialize();

public:
    void AddCamera(E_Camera* cam);
    void Render();
};
