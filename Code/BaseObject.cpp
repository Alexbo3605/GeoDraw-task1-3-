#include "BaseObject.h"

BaseObject::BaseObject(void) : p_id_Obj(-1)
{}

BaseObject::BaseObject(int id) : p_id_Obj(id)
{}

BaseObject::~BaseObject()
{}

int BaseObject::get_Id() const
{
    return p_id_Obj;
}