#include "SFMLCircleDecorator.h"

SFMLCircleDecorator::SFMLCircleDecorator(Circle& cr, sf::RenderWindow* window) 
	: circle(cr), window(window)
{
	circleShape = new sf::CircleShape();
	initializeShape();
}

SFMLCircleDecorator::~SFMLCircleDecorator()
{
	delete circleShape;
}

BoundingBox SFMLCircleDecorator::AABB() const
{
	return circle.AABB();
}

void SFMLCircleDecorator::serialize(IDataProvider::IDataReader* dr) const
{
	circle.serialize(dr);
}

void SFMLCircleDecorator::deserialize(IDataProvider::IDataReader* dr, int size)
{
	circle.deserialize(dr, size);
}

void SFMLCircleDecorator::initializeShape()
{
	Point2d center = *circle.get_Circle_Center();
	double radius = circle.get_Circle_Radius();

	circleShape->setRadius(static_cast<float>(radius));
	circleShape->setPosition(static_cast<float>(center.x() - radius), static_cast<float>(center.y() - radius));
	circleShape->setFillColor(sf::Color::White);
}

void SFMLCircleDecorator::draw()
{
	this->window->draw(*circleShape);
}
