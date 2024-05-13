#include "DataReader.h"

DataReader::DataReader(void)
{
	dp = new DataProvider();
}

DataReader::~DataReader(void)
{
	delete dp;
}
//void DataReader::clear_Memory()
//{
//	for (auto& i : objects)
//	{
//		delete i;
//	}
//	objects.clear();
//}


void DataReader::read_Array(std::vector<BaseObject*> &objects_Out)
{
	const int objectCount = dp->rdInt();
	
	objects_Out.reserve(objectCount);


	//створюєм обєкти
	for (int i = 0; i < objectCount; i++)
	{
		BaseObject* obj = read_Object();

		/*obj->showAll();*/

		if (obj != nullptr) {
			objects_Out.push_back(obj);
		}
	}
}

BaseObject* DataReader::read_Object()
{
	const int objectType = dp->rdInt();
	const int objectSize = dp->rdInt();
	BaseObject* obj = ObjectFactory::factory(objectType);

	if (obj == nullptr) { //мб тут теж перевірка чи виділилася пам'ять
		obj = new Unknown(objectType);
	}
	
	try {
		obj->deserialize(*dp, objectSize);
	}
	catch (ReadError& ex) {

		obj->~BaseObject();
		obj = nullptr;

		/*ex.getError(); записати у лог файл*/
	}
	catch (EndOfFile& ex) {
		std::cout <<"End of file " << std::endl;
		/*ex.getError(); записати у лог файл*/
	}

	return obj;
}