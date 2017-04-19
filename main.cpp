///Include Manager
#include "E_Manager.h"
#include "E_Renderer.h"
#include "E_Camera.h"
#include "E_Object.h"


int main()
{
    E_Object* obj = new E_Object();
    E_Object* obj1 = new E_Object();

    E_Camera* camera = new E_Camera();

    E_Renderer* renderer = new E_Renderer();

    renderer->SetCamera(camera);

    renderer->AddObject(obj);
    renderer->AddObject(obj1);

    renderer->Render();


    //Previous Code
    // E_Manager* Mgr = new E_Manager();


    return EXIT_SUCCESS;
}
