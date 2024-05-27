#pragma once
#include "Point2d.h"
#include "BoundingBox.h"
#include "Settings.h"
#include "IDataProvider.h"

#include <iostream>

class BaseObject {
public:
    BaseObject(void);
    BaseObject(int id);
    virtual ~BaseObject(void);

    int get_Id() const;
    virtual void showAll() = 0;
    virtual BoundingBox AABB() const = 0;

    virtual void serialize(IDataProvider::IDataReader* dr) const = 0;
    virtual void deserialize(IDataProvider::IDataReader* dr, int size) = 0;

protected:
    int p_id_Obj;
};