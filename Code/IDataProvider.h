#pragma once

//#include "BaseObject.h"

#include "Exceptions.h"
#include "Settings.h"
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

        virtual bool isEnd() = 0;
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

protected:
    template<typename T>
    BaseObject* read_Object_temp(T* reader);

    template<typename T>
    void readIn_temp(T* reader, std::vector<BaseObject*>& outputObjects);

    inline virtual BaseObject* createObject(const int id) = 0;
};


template<typename T>
BaseObject* IDataProvider::read_Object_temp(T* reader) {

    const int objectType = reader->rdInt();
    const int objectSize = reader->rdInt();
    BaseObject* obj = createObject(objectType);
    try {
        obj->deserialize(reader, objectSize);
    }
    catch (IOError& ex) {
        delete obj;
        obj = nullptr;
        std::ofstream logFile(EXEPTION_LOG_FILENAME, std::ios::app);
        if (logFile.is_open()) {
            logFile << ex.getError() << std::endl;
            logFile.close();
        }
    }
    catch (EndOfFile) {
        std::ofstream logFile(EXEPTION_LOG_FILENAME, std::ios::app);
        if (logFile.is_open()) {
            IOError openError("End of file", __LINE__);
            logFile << openError.getError() << std::endl;
            logFile.close();
        }
        delete obj;
        obj = nullptr;
        throw;
    }
    catch (std::bad_alloc) {
        std::ofstream logFile(EXEPTION_LOG_FILENAME, std::ios::app);
        if (logFile.is_open()) {
            IOError openError("function 'ObjectFactory::factory' memory was not allocated", __LINE__);
            logFile << openError.getError() << ": " << typeid(T).name() << std::endl;
            logFile.close();
        }
        return nullptr;
    }
    return obj;
}

template<typename T>
void IDataProvider::readIn_temp(T* reader, std::vector<BaseObject*>& outputObjects) {
    reader->setCurrent(COUNT_OBJECTS_POS);

    if (reader->isEnd()) {
        return;
    }

    const int objectCount = reader->rdInt();
    outputObjects.reserve(objectCount + outputObjects.size());

    BaseObject* obj = nullptr;
    for (int i = 0; i < objectCount; i++) {
        try {
            obj = read_Object_temp(reader);
            if (obj != nullptr) {
                outputObjects.push_back(obj);
            }
        }
        catch (EndOfFile) {
            break;
        }
    }
}
