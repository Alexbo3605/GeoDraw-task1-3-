#include "ArrayDataProvider.h"

const std::vector<double> arrData = {
    8, // -- ����� �������� � �����

    1, // 1 -- ��� "�������" �� ���������, ������������� ���� ���������
    4, // 4 -- ���������� ����� double (������� ���������� � � 2�� �������!!) ��
    0.0, 0.0, // ���������� - ����� ������ ����
    10.0, 10.0, // ���������� - ������ ������� ����



    2, // 2 -- ��� "����������"
    3,
    0.0, 0.0, // ���������� - ����� ����������
    25.0, // ������ ����������



    3, // 3 -- ���� ����������� ���
    5,
    1., 2., 3., 4., 5., // ������



    4, // 4 - ���� ����������
    5,
    150., 150.,  // ���������� -- ����� ����������
    44.,         // ������ ����������
    PI / 4., PI / 2., // ����� -- ������ � ����� ����


    2, // 2 -- ��� "����������"
    3,
    10.0, THROW_ERR, // ��� ������ ������� ���������� ����������
    25.0,



    5, // 5 -- ��� �������������
    10,
    10., 20., // ���������� �����
    20., 30., // ���������� �����
    35., 25., // ���������� �����
    0., 50., // ���������� �����
    0., 0.,   // ���������� �����



    6, // -- ��� "�������"
    10,
    0,0, // ���������� �����
    1,1, // ���������� �����
    0,1, // ���������� �����
    0,2, // ���������� �����
    5,5, // ���������� �����


    28, // ����������� ������
    10,
    90,91,92,93,94,95,96,97,98,99
};



///---------------Constructors-------------///
ArrayDataProvider::ArrayDataProvider(void) : IDataProvider()
{
    arrDataReader = new ArrayDataReader();
}
ArrayDataProvider::ArrayDataProvider(std::vector<double>& arr) : IDataProvider()
{
    arrDataReader = new ArrayDataReader(arr);
}
ArrayDataProvider::~ArrayDataProvider(void)
{
    delete arrDataReader;
}

ArrayDataProvider::ArrayDataReader::ArrayDataReader() : IDataReader(arrData.size()), p_arrData(arrData)
{}

ArrayDataProvider::ArrayDataReader::ArrayDataReader(std::vector<double>& arr) : IDataReader(arr.size()), p_arrData(arr)
{}

ArrayDataProvider::ArrayDataReader::~ArrayDataReader(void)
{}



///---------------ArrayDataReader-------------///
void ArrayDataProvider::ArrayDataReader::checkCurr()
{
    if (p_current >= p_maxCurrent) {
        throw EndOfFile();
    }
}

int ArrayDataProvider::ArrayDataReader::rdInt(const int remainder)
{
    checkCurr();
    const int i = p_arrData[p_current++];
    if (i == THROW_ERR) {
        p_current += remainder;
        throw ReadError("Error reding Int pos", p_current - remainder);
    }
    return i;
}

double ArrayDataProvider::ArrayDataReader::rdDouble(const int remainder)
{
    checkCurr();
    const double d = p_arrData[p_current++];
    if (d == THROW_ERR) {
        p_current += remainder;
        throw ReadError("Error reding Double pos", p_current - remainder);
    }
    return d;
}


void ArrayDataProvider::ArrayDataReader::wrInt(const int number)
{
    p_arrData.push_back(number);
    ++p_maxCurrent;
}

void ArrayDataProvider::ArrayDataReader::wrDouble(const double number)
{
    p_arrData.push_back(number);
    ++p_maxCurrent;
}

void ArrayDataProvider::ArrayDataReader::changeObjectsCount(const int delta)
{
    // delta is the difference between the initial number of objects
    // (before write) and the final one
    if (!p_arrData.empty()) {
        p_arrData[COUNT_OBJECTS_POS] += delta;
    }
}

void ArrayDataProvider::ArrayDataReader::setCurrent(const int newCurrent)
{
    p_current = newCurrent;
}




///---------------ArrayDataProvider-------------///
///-----------Write
void ArrayDataProvider::write_Object(BaseObject* obj)
{
    //write object ID
    arrDataReader->wrInt(obj->get_Id());

    //write object Data
    obj->serialize(arrDataReader);
}

bool ArrayDataProvider::writeFrom(const std::vector<BaseObject*>& inputObjects)
{
    if (inputObjects.empty()) {
        return false;
    }
    if (arrDataReader == nullptr) {
        return false;
    }

    size_t index = 0;
    for (auto& i : inputObjects)
    {
        write_Object(i);

        ++index;
    }
    arrDataReader->changeObjectsCount(index);
    return true;
}



///-----------Read
BaseObject* ArrayDataProvider::read_Object()
{
    const int objectType = arrDataReader->rdInt();
    const int objectSize = arrDataReader->rdInt();
    BaseObject* obj = ObjectFactory::factory(objectType);

    try {
        obj->deserialize(arrDataReader, objectSize);
    }
    catch (ReadError& ex) {

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
            logFile << "End of file" << std::endl;
            logFile.close();
        }
        delete obj;
        obj = nullptr;

        throw; // generate the same exception
    }
    catch (std::bad_alloc)
    {
        std::ofstream logFile(EXEPTION_LOG_FILENAME, std::ios::app);
        if (logFile.is_open()) {
            logFile << "function 'ObjectFactory::factory' memory was not allocated" << std::endl;
            logFile.close();
        }
        return nullptr;
    }
    return obj;
}


void ArrayDataProvider::readIn(std::vector<BaseObject*>& outputObjects)
{
    arrDataReader->setCurrent(COUNT_OBJECTS_POS);
    const int objectCount = arrDataReader->rdInt();

    outputObjects.reserve(objectCount + outputObjects.size());

    BaseObject* obj = nullptr;

    for (int i = 0; i < objectCount; i++)
    {
        try
        {
            obj = read_Object();

            if (obj != nullptr) {
                outputObjects.push_back(obj);
            }
        }
        catch (EndOfFile)
        {
            break;
        }
    }
}





