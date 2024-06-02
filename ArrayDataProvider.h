#pragma once
//#include "IDataProvider.h"
#include "ObjectFactory.h"
//#include "BaseObject.h"

class ArrayDataProvider : public IDataProvider
{
public:
    class ArrayDataReader : public IDataReader 
    {
    public:
        ArrayDataReader(void);
        ArrayDataReader(std::vector<double>& arr);
        virtual ~ArrayDataReader(void);

        virtual int rdInt(const int remainder = 0) override;
        virtual double rdDouble(const int remainder = 0) override;

        virtual void wrInt(const int number) override;
        virtual void wrDouble(const double number) override;

        void changeObjectsCount(const int delta);
        virtual void setCurrent(const int newCurrent) override;
        virtual bool isEnd() override;
    private:
        virtual void checkCurr() override;
        
        std::vector<double> p_arrData;
    };

    ArrayDataProvider(void);
    ArrayDataProvider(std::vector<double>& arr);
    virtual ~ArrayDataProvider(void);

    virtual void readIn(std::vector<BaseObject*>& outputObjects) override;
    virtual bool writeFrom(const std::vector<BaseObject*>& inputObjects) override;

private:
    void write_Object(BaseObject*);
    BaseObject* read_Object();
    inline virtual BaseObject* createObject(const int objectId) override;

    ArrayDataReader* arrDataReader;
};

