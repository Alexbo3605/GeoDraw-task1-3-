#pragma once
#include "Exceptions.h"

#include <fstream>
#include <vector>

class BaseObject;

class IDataProvider {
public:

    class IDataReader
    {
    public:
        IDataReader(const int maxCur);
        virtual ~IDataReader(void);


        virtual int rdInt(const int remainder = 0) = 0;
        virtual double rdDouble(const int remainder = 0) = 0;

        virtual void wrInt(const int number) = 0;
        virtual void wrDouble(const double number) = 0;

        virtual void setCurrent(const int newCurrent) = 0;
    protected:
        int p_current;
        int p_maxCurrent;
        virtual void checkCurr() = 0;
    };

    IDataProvider(void);
    virtual ~IDataProvider(void);

    //read objects from subjects and record them
    virtual void readIn(std::vector<BaseObject*>& outputObjects) = 0;

    //write objects in objects
    virtual bool writeFrom(const std::vector<BaseObject*>& inputObjects) = 0;
};

