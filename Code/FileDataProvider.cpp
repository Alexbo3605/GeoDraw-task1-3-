#include "FileDataProvider.h"

///---------------Constructors-------------///

FileDataProvider::FileDataProvider(std::string fileName) :
    IDataProvider()
{
    fileDataReader = new FileDataReader(fileName);
}

FileDataProvider::~FileDataProvider(void)
{
    delete fileDataReader;
}


// 0 is the initial file size
FileDataProvider::FileDataReader::FileDataReader(std::string fileName)
    : IDataReader(0), p_DataFileName(fileName)
{
    p_file.open(fileName, std::ios::binary | std::ios::in | std::ios::out);

    if (!p_file.is_open())
    {
        std::ofstream logFile(EXEPTION_LOG_FILENAME, std::ios::app);

        if (logFile.is_open())
        {
            IOError openError("Failed to open file", __LINE__);
            logFile << openError.getError() << ": " << fileName << std::endl;

            //create file
            p_file.open(fileName, std::ios::binary | std::ios::out);
            if (p_file.is_open()) {
                p_file.close();
            }
            else {
                IOError createError("Failed to create file", __LINE__);
                logFile << createError.getError() << ": " << fileName << std::endl;
            }

            // Attempt to reopen in read/write mode
            p_file.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
            if (!p_file.is_open()) {
                IOError reopenError("Failed to open newly created file", __LINE__);
                logFile << reopenError.getError() << ": " << fileName << std::endl;
            }

            logFile.close();
        }
    }
}

FileDataProvider::FileDataReader::~FileDataReader(void)
{
    if (p_file.is_open())
    {
        p_file.close();
    }
}

///---------------FileDataReader-------------///
int FileDataProvider::FileDataReader::rdInt(const int remainder)
{
    checkCurr();
    int value;
    p_file.read(reinterpret_cast<char*>(&value), sizeof(value));
    p_current += sizeof(value);
    return value;
}

double FileDataProvider::FileDataReader::rdDouble(const int remainder)
{
    checkCurr();
    double value;
    p_file.read(reinterpret_cast<char*>(&value), sizeof(value));
    p_current += sizeof(value);
    return value;
}

void FileDataProvider::FileDataReader::wrInt(const int number)
{
    p_file.write(reinterpret_cast<const char*>(&number), sizeof(number));
    p_maxCurrent += sizeof(number);
}

void FileDataProvider::FileDataReader::wrDouble(const double number)
{
    p_file.write(reinterpret_cast<const char*>(&number), sizeof(number));
    p_maxCurrent += sizeof(number);
}

void FileDataProvider::FileDataReader::setCurrent(const int newCurrent)
{
    if (p_maxCurrent > newCurrent) {
        p_current = newCurrent;
        p_file.seekg(newCurrent, std::ios::beg);
    }
    else {
        throw EndOfFile();
    }
}

bool FileDataProvider::FileDataReader::isEnd()
{
    return p_file.eof();
}

int FileDataProvider::FileDataReader::getCurrent()
{
    return p_current;
}

void FileDataProvider::FileDataReader::checkCurr()
{
    if (p_current >= p_maxCurrent) {
        throw EndOfFile();
    }
}



///---------------FileDataProvider-------------///
///-----------Writing to a file
/// 
bool FileDataProvider::writeFrom(const std::vector<BaseObject*>& inputObjects)
{
    if (fileDataReader == nullptr) {
        return false;
    }
    //record the number of objects
    fileDataReader->wrInt(inputObjects.size());

    for (auto& i : inputObjects)
    {
        write_Object(i);
    }
    return true;
}



void FileDataProvider::write_Object(BaseObject* obj)
{
    //write object ID
    fileDataReader->wrInt(obj->get_Id());

    //write object Size and Data 
    obj->serialize(fileDataReader);
}


///-----------Reading the file
void FileDataProvider::readIn(std::vector<BaseObject*>& outputObjects)
{
    readIn_temp(fileDataReader, outputObjects);
}

BaseObject* FileDataProvider::read_Object()
{
    return read_Object_temp(fileDataReader);
}

inline BaseObject* FileDataProvider::createObject(const int objectId)
{
    return  ObjectFactory::factory(objectId);;
}



void FileDataProvider::erroReadIn(std::vector<BaseObject*>& outputObjects)
{
    //get to the beginning of the file
    fileDataReader->setCurrent(COUNT_OBJECTS_POS);

    if (fileDataReader->isEnd()) {
        return;
    }

    //read the number of objects in the file
    const int objectCount = fileDataReader->rdInt();

    outputObjects.reserve(objectCount + outputObjects.size());

    BaseObject* obj = nullptr;

    for (int i = 0; i < objectCount; i++)
    {
        try {
            // artificially throw EndOfFile for testing
            if (i == 5) { // throw error on the third object
                throw EndOfFile();
            }
            obj = errorRead_Object();

            if (obj != nullptr) {
                outputObjects.push_back(obj);
            }
        }
        catch (EndOfFile) {
            std::ofstream logFile(EXEPTION_LOG_FILENAME, std::ios::app);
            if (logFile.is_open()) {
                logFile << "End of file reached while reading object #" << i << std::endl;
                logFile.close();
            }
            break;
        }
    }
}

BaseObject* FileDataProvider::errorRead_Object()
{
    static int callCount = 0;
    callCount++;



    const int objectType = fileDataReader->rdInt();
    const int objectSize = fileDataReader->rdInt();
    BaseObject* obj = ObjectFactory::factory(objectType);

    try {

        if (callCount == 1) { // throw error on the first call
            throw std::bad_alloc();
        }


        obj->deserialize(fileDataReader, objectSize);    
        
        if (callCount == 3) { // throw error on the first call
            throw IOError("Test Error cont elem 4", __LINE__);
        }
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
            logFile << openError.getError() << ": FileDataProvider " << std::endl;
            logFile.close();
        }
        delete obj;
        obj = nullptr;

        throw; // generate the same exception
    }
    catch (std::bad_alloc)
    {
        fileDataReader->setCurrent(fileDataReader->getCurrent() + (sizeof(double) * objectSize));
        std::ofstream logFile(EXEPTION_LOG_FILENAME, std::ios::app);
        if (logFile.is_open()) {
            IOError openError("function 'ObjectFactory::factory' memory was not allocated", __LINE__);
            logFile << openError.getError() << ": FileDataProvider " << std::endl;
            logFile.close();
        }
        return nullptr;
    }
    return obj;
}
