// CivilDeveloperTask.cpp : Defines the entry point for the console application.
//


#include "ArrayDataProvider.h"
#include "FileDataProvider.h"

#include <tchar.h>


int _tmain(int argc, _TCHAR* argv[])
{

	ArrayDataProvider* arr = new ArrayDataProvider();

	std::vector<BaseObject*> objects;
	std::cout << "--------------------read Arr--------------------" << std::endl;
	arr->readIn(objects);
	for (auto& i : objects)
	{
		i->showAll();
	}


	FileDataProvider* fileArr = new FileDataProvider(DATA_FILENAME);
	std::cout << "--------------------write File--------------------" << std::endl;
	if (fileArr->writeFrom(objects))
	{
		std::vector<BaseObject*> readObjects;
		std::cout << "--------------------read File--------------------" << std::endl;
		fileArr->readIn(readObjects);

		for (auto& i : readObjects)
		{
			i->showAll();
		}

	}

	delete arr;
	delete fileArr;

	return 0;
}



