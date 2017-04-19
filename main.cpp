///Include Manager
#include "E_Manager.h"
#include "E_Renderer.h"
#include "E_Camera.h"
#include "E_Object.h"


int main()
{
    E_Object* obj = new E_Object();
    E_Camera* camera = new E_Camera();

    E_Renderer* renderer = new E_Renderer();
    renderer->AddCamera(camera);


    //Previous Code
    E_Manager* Mgr = new E_Manager();


    return EXIT_SUCCESS;
}
