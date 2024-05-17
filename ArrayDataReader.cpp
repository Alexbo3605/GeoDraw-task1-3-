#include "ArrayDataReader.h"


ArrayDataReader::ArrayDataReader(void)
{
	dp = new DataProvider();
}

ArrayDataReader::~ArrayDataReader(void)
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


void ArrayDataReader::read(std::vector<BaseObject*>& objects_Out)
{
	const int objectCount = dp->rdInt();

	objects_Out.reserve(objectCount);

	BaseObject* obj = nullptr;
	//створюєм обєкти
	for (int i = 0; i < objectCount; i++)
	{
		try 
		{
			obj = read_Object();
		}
		catch (EndOfFile) 
		{
			break;
		}

		if (obj != nullptr) {
			objects_Out.push_back(obj);
		}
		
	}
}

BaseObject* ArrayDataReader::read_Object()
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

		std::ofstream logFile(exeption_Log_Filename, std::ios::app);
		if (logFile.is_open()) {
			logFile << ex.getError() << std::endl;
			logFile.close();
		}

	}
	catch (EndOfFile) {

		std::ofstream logFile(exeption_Log_Filename, std::ios::app); 
		if (logFile.is_open()) { 
			logFile << "End of file" << std::endl; 
			logFile.close(); 
		}
		obj->~BaseObject(); 
		obj = nullptr;

		throw; // generate the same exception
	}
	catch (std::bad_alloc)
	{
		std::ofstream logFile(exeption_Log_Filename, std::ios::app);
		if (logFile.is_open()) {
			logFile << "function 'ObjectFactory::factory' memory was not allocated" << std::endl;
			logFile.close();
		}
		return nullptr;
	}

	return obj;
}