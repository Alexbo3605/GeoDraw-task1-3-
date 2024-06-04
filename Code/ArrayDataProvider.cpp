#include "ArrayDataProvider.h"

const std::vector<double> arrData = {
    8, // -- число объектов в файле

    1, // 1 -- тип "квадрат" со сторонами, параллельными осям координат
    4, // 4 -- количество чисел double (зробити констуктор і з 2ма точками!!) хм
    10.0, 10.0, // координаты - левый нижний угол
    100.0, 100.0, // координаты - правый верхний угол



    2, // 2 -- тип "окружность"
    3,
    200.0, 50.0, // координаты - центр окружности
    25.0, // радиус окружности



    3, // 3 -- пока неизвестный тип
    5,
    1., 2., 3., 4., 5., // данные



    4, // 4 - дуга окружности
    5,
    250., 250.,  // координаты -- центр окружности
    44.,         // радиус окружности
    PI / 4., PI / 2., // уголы -- начало и конец дуги


    2, // 2 -- тип "окружность"
    3,
    10.0, THROW_ERR, // при чтении объекта выбросится исключение
    25.0,



    5, // 5 -- тип многоугольник
    10,
    200., 400., // координаты точки
    400., 600., // координаты точки
    350., 250., // координаты точки
    0., 500., // координаты точки
    0., 250.,   // координаты точки



    6, // -- тип "ломаная"
    10,
    300,100, // координаты точки
    350,100, // координаты точки
    400,200, // координаты точки
    500,300, // координаты точки
    300,200, // координаты точки


    28, // неизвестный объект
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








