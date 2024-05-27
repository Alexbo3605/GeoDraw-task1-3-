#pragma once
#include "ObjectFactory.h"

#include <fstream>
class FileDataProvider : public IDataProvider
{
public:
    class FileDataReader : public IDataReader
    {
    public:
        FileDataReader(std::string fileName);
        virtual ~FileDataReader(void);

        virtual int rdInt(const int remainder = 0) override;
        virtual double rdDouble(const int remainder = 0) override;

        virtual void wrInt(const int number) override;
        virtual void wrDouble(const double number) override;

        virtual void setCurrent(const int newCurrent) override;
        bool fileEmpty();

    private:
        virtual void checkCurr() override;

        std::fstream p_file;
        std::string p_DataFileName;
    };
    FileDataProvider(std::string fileName);
    virtual ~FileDataProvider(void);

    virtual void readIn(std::vector<BaseObject*>& outputObjects) override;
    virtual bool writeFrom(const std::vector<BaseObject*>& inputObjects) override;

private:
    FileDataReader* fileDataReader;

    void write_Object(BaseObject* obj);
    BaseObject* read_Object();
};