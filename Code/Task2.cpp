// CivilDeveloperTask.cpp : Defines the entry point for the console application.
//


#include "ArrayDataProvider.h"
#include "FileDataProvider.h"

#include "SFMLWindowFacade.h"

#include <tchar.h>

#include <thread>
#include <chrono>


//#include <SFML/Graphics.hpp>
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//
//	return 0;
//}

int _tmain(int argc, _TCHAR* argv[])
{

	ArrayDataProvider* arr = new ArrayDataProvider();

	std::vector<BaseObject*> objects;
	std::cout << "--------------------read Arr--------------------" << std::endl;
	arr->readIn(objects);
	for (auto& i : objects)
	{
		i->draw();
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
			i->draw();
		}

	}


	SFMLWindowFacade* fc = new SFMLWindowFacade(objects);
	fc->run();
	
	delete fc;
	delete arr;
	delete fileArr;

	return 0;
}



