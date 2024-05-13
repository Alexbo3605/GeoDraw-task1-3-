#pragma once

#include <iostream>

#include "Point2d.h"
#include "DataProvider.h"
#include "BoundingBox.h"
#include "Settings.h"
//#include "ObjectFactory.h"

class BaseObject {
public:
    BaseObject(void);
    BaseObject(int id);

    virtual ~BaseObject(void);

    int get_Id() const;

    virtual void showAll() = 0; //чиста віртуальна функція

    virtual BoundingBox AABB() const = 0;
    
    //virtual void serialize(std::ostream& out) const = 0;
    // 
    virtual void deserialize(DataProvider& dp, int size) = 0; //чиста віртуальна функція


protected:
    int p_id_Obj;
};