#pragma once


#include "ObjectFactory.h"
#include "Exceptions.h"

class IDataReader
{
public:
    IDataReader(void);

    virtual ~IDataReader(void);

    virtual void read(std::vector<BaseObject*>& objects) =0; //використати патерн Будівельник (не факт)

private:

};