#include "ArrayDataProvider.h"

const std::vector<double> arrData = {
    8, // -- ����� �������� � �����

    1, // 1 -- ��� "�������" �� ���������, ������������� ���� ���������
    4, // 4 -- ���������� ����� double (������� ���������� � � 2�� �������!!) ��
    10.0, 10.0, // ���������� - ����� ������ ����
    100.0, 100.0, // ���������� - ������ ������� ����



    2, // 2 -- ��� "����������"
    3,
    200.0, 50.0, // ���������� - ����� ����������
    25.0, // ������ ����������



    3, // 3 -- ���� ����������� ���
    5,
    1., 2., 3., 4., 5., // ������



    4, // 4 - ���� ����������
    5,
    250., 250.,  // ���������� -- ����� ����������
    44.,         // ������ ����������
    PI / 4., PI / 2., // ����� -- ������ � ����� ����


    2, // 2 -- ��� "����������"
    3,
    10.0, THROW_ERR, // ��� ������ ������� ���������� ����������
    25.0,



    5, // 5 -- ��� �������������
    10,
    200., 400., // ���������� �����
    400., 600., // ���������� �����
    350., 250., // ���������� �����
    0., 500., // ���������� �����
    0., 250.,   // ���������� �����



    6, // -- ��� "�������"
    10,
    300,100, // ���������� �����
    350,100, // ���������� �����
    400,200, // ���������� �����
    500,300, // ���������� �����
    300,200, // ���������� �����


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

bool ArrayDataProvider::ArrayDataReader::isEnd()
{
    return p_current >= p_maxCurrent;
}

int ArrayDataProvider::ArrayDataReader::rdInt(const int remainder)
{
    checkCurr();
    const int i = p_arrData[p_current++];
    if (i == THROW_ERR) {
        p_current += remainder;
        throw IOError("Error reding Int pos", __LINE__);
    }
    return i;
}

double ArrayDataProvider::ArrayDataReader::rdDouble(const int remainder)
{
    checkCurr();
    const double d = p_arrData[p_current++];
    if (d == THROW_ERR) {
        p_current += remainder;
        throw IOError("Error reding Double pos", __LINE__);
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
    return read_Object_temp(arrDataReader);
}

void ArrayDataProvider::readIn(std::vector<BaseObject*>& outputObjects)
{
    readIn_temp(arrDataReader, outputObjects);
}

inline BaseObject* ArrayDataProvider::createObject(const int objectId)
{
    return ObjectFactory::factory(objectId);
}








