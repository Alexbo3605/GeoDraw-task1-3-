// CivilDeveloperTask.cpp : Defines the entry point for the console application.
//


#include "ObjectFactory.h"

//#include "IDataReader.h"

#include "ArrayDataReader.h"
#include <tchar.h>


int _tmain(int argc, _TCHAR* argv[])
{



	ArrayDataReader* dr = new ArrayDataReader();
	
	std::vector<BaseObject*> objects;


	dr->read(objects); 

	std::cout <<"size!!!!!!!  " << objects.size() << std::endl;
	for (auto& i : objects)
	{
		i->showAll();
	}

	delete dr;
	return 0;
}



