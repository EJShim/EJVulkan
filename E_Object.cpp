#include "E_Object.h"
#include <iostream>

E_Object::E_Object()
{
    std::cout << "Object Initialized" << std::endl;
}

E_Object::~E_Object()
{

}

void E_Object::Update()
{
    std::cout << "Object Update" << std::endl;
}
