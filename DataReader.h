#pragma once


#include "ObjectFactory.h"
#include "Exceptions.h"

class DataReader
{
public:
    DataReader(void);
    virtual ~DataReader(void);

    virtual void read_Array(std::vector<BaseObject*> &objects); //використати патерн Будівельник (не факт)
    /*virtual void read_Array(std::vector<std::unique_ptr<BaseObject>>& objects_Out);*/

    
private:
    void clear_Memory();
    virtual BaseObject* read_Object();

    DataProvider* dp;

    /*std::vector<BaseObject*> objects;*/
};