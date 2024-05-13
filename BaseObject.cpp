#include "BaseObject.h"



BaseObject::BaseObject(void) : p_id_Obj(-1)
{}

BaseObject::BaseObject(int id) : p_id_Obj(id)
{}

int BaseObject::get_Id() const
{
    return p_id_Obj;
}

BaseObject::~BaseObject() {
    std::cout << "~BaseObject()" << std::endl;
}





