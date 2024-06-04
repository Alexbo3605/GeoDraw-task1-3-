#include "SFMLWindowFacade.h"

SFMLWindowFacade::SFMLWindowFacade(std::vector<BaseObject*> objectsArray) 
	: objectsArray(objectsArray),
	videoMode(std::make_unique<sf::VideoMode>(windowWidth, windowHeight)),
	settings(std::make_unique<sf::ContextSettings>()),
	ev(std::make_unique<sf::Event>()),
	menu(std::make_unique<sf::RectangleShape>(sf::Vector2f(windowWidth, windowHeight)))
{

	this->initWindow();
	transformToSFMLObjects();
}

void SFMLWindowFacade::initWindow()
{
	settings->antialiasingLevel = antialiasingLevel;
	this->menu->setFillColor(sf::Color::Black);

	this->window = std::make_unique<sf::RenderWindow>(*this->videoMode, "Task2", sf::Style::Titlebar | sf::Style::Close, *this->settings);
	this->window->setFramerateLimit(FPS);
}

void SFMLWindowFacade::transformToSFMLObjects()
{

	for (const auto& obj : objectsArray)
	{
		try
		{
			if (typeid(*obj) == typeid(Circle))
			{
				Circle* circlePtr = dynamic_cast<Circle*>(obj);

				if (circlePtr)
				{
					auto sfmlCircleDecorator = std::make_unique<SFMLCircleDecorator>(*circlePtr, window.get());
					SFMLobjectsArray.push_back(std::move(sfmlCircleDecorator));
				}
			}
			else if (typeid(*obj) == typeid(CircularArc))
			{
				CircularArc* arcPtr = dynamic_cast<CircularArc*>(obj);
				if (arcPtr)
				{
					auto sfmlArcDecorator = std::make_unique<SFMLCircularArcDecorator>(*arcPtr, window.get());
					SFMLobjectsArray.push_back(std::move(sfmlArcDecorator));
				}
			}
			else if (typeid(*obj) == typeid(Polygon))
			{
				Polygon* polyPtr = dynamic_cast<Polygon*>(obj);
				if (polyPtr)
				{
					auto sfmlPolyDecorator = std::make_unique<SFMLPolygonDecorator>(*polyPtr, window.get());
					SFMLobjectsArray.push_back(std::move(sfmlPolyDecorator));
				}
			}
			else if (typeid(*obj) == typeid(Polyline))
			{
				Polyline* polylinePtr = dynamic_cast<Polyline*>(obj);
				if (polylinePtr)
				{
					auto sfmlPolylineDecorator = std::make_unique<SFMLPolylineDecorator>(*polylinePtr, window.get());
					SFMLobjectsArray.push_back(std::move(sfmlPolylineDecorator));
				}
			}
			else if (typeid(*obj) == typeid(Rectangle))
			{
				Rectangle* rectPtr = dynamic_cast<Rectangle*>(obj);
				if (rectPtr)
				{
					auto sfmlRectDecorator = std::make_unique<SFMLRectangleDecorator>(*rectPtr, window.get());
					SFMLobjectsArray.push_back(std::move(sfmlRectDecorator));
				}
			}
		}
		catch (const std::bad_alloc&)
		{
			std::ofstream logFile(EXEPTION_LOG_FILENAME, std::ios::app);
			if (logFile.is_open()) {
				logFile << "function 'SFMLObjectsFactory::factory' memory was not allocated" << std::endl;
				logFile.close();
			}
		}
		catch (const std::bad_cast&)
		{
			std::ofstream logFile(EXEPTION_LOG_FILENAME, std::ios::app);
			if (logFile.is_open()) {
				logFile << "function 'SFMLObjectsFactory::factory' bad_cast exception" << std::endl;
				logFile.close();
			}
		}
	}
}

SFMLWindowFacade::~SFMLWindowFacade()
{
	for (auto& i : objectsArray)
	{
		delete i;
	}
	SFMLobjectsArray.clear();
}


const bool SFMLWindowFacade::isRunning() const
{
	return this->window->isOpen();
}

void SFMLWindowFacade::run()
{
	/*static int count = 0;*/
	while (this->isRunning())
	{
		/*std::cout << count++ << std::endl;*/
		this->update();
		this->render();
	}
}



void SFMLWindowFacade::pollEvents()
{
	while (this->window->pollEvent(*this->ev)) {
		if (this->ev->type == sf::Event::Closed)
			this->window->close();
	}
}

void SFMLWindowFacade::update()
{
	this->pollEvents();
}


void SFMLWindowFacade::render()
{
	this->window->clear();
	
	/*this->window->draw(*this->menu);*/
	for (auto& i : this->SFMLobjectsArray)
	{
		
		i->draw(); //метод малює в UI
	}

	this->window->display(); 
}



