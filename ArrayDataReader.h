#pragma once

#include "IDataReader.h"

class ArrayDataReader : public IDataReader
{
public:
    ArrayDataReader(void);
    virtual ~ArrayDataReader(void);

    virtual void read(std::vector<BaseObject*>& objects); //використати патерн Будівельник (не факт)


private:
    /*virtual*/ BaseObject* read_Object();

    DataProvider* dp;

    /*std::vector<BaseObject*> objects;*/
};

