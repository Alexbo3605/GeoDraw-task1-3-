#pragma once

#include "ObjectFactory.h"
#include "SFMLCircleDecorator.h"
#include "SFMLCircularArcDecorator.h"
#include "SFMLPolygonDecorator.h"
#include "SFMLPolylineDecorator.h"
#include "SFMLRectangleDecorator.h"

#include <memory>

class SFMLWindowFacade
{
private:
	void initWindow();
	void pollEvents();
	void update();
	void render();
	void transformToSFMLObjects();

	std::unique_ptr<sf::ContextSettings> settings;
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<sf::VideoMode> videoMode;
	std::unique_ptr<sf::Event> ev;
	std::unique_ptr<sf::RectangleShape> menu;

	std::vector<BaseObject*> objectsArray;
	std::vector < std::unique_ptr<BaseObject> > SFMLobjectsArray;
public:
	SFMLWindowFacade(std::vector<BaseObject*> objectsArray);
	virtual ~SFMLWindowFacade();

	const bool isRunning() const;
	void run();
};

