#include "SFMLRectangleDecorator.h"

SFMLRectangleDecorator::SFMLRectangleDecorator(Rectangle& rect, sf::RenderWindow* window) 
    : rectangle(rect), window(window)
{
	rectangleShape = new sf::RectangleShape();
	initializeRectangleShape();
}

SFMLRectangleDecorator::~SFMLRectangleDecorator()
{
	delete rectangleShape;
}

BoundingBox SFMLRectangleDecorator::AABB() const
{
    return rectangle.AABB();
}

void SFMLRectangleDecorator::serialize(IDataProvider::IDataReader* dr) const
{
	rectangle.serialize(dr);
}

void SFMLRectangleDecorator::deserialize(IDataProvider::IDataReader* dr, int size)
{
	rectangle.deserialize(dr, size);
}

void SFMLRectangleDecorator::initializeRectangleShape()
{
    const Point2d topLeft = *rectangle.get_Rectangle_Top_Left_Point();
    const Point2d bottomRight = *rectangle.get_Rectangle_Bottom_Right_Point();

    // ¬изначаЇмо позиц≥ю та розм≥р
    float width = bottomRight.x() - topLeft.x();
    float height = bottomRight.y() - topLeft.y();

    rectangleShape->setPosition(topLeft.x(), topLeft.y());
    rectangleShape->setSize(sf::Vector2f(width, height));
    rectangleShape->setFillColor(sf::Color::White);
    rectangleShape->setOutlineColor(sf::Color::White);
    rectangleShape->setOutlineThickness(1.0f);
}

void SFMLRectangleDecorator::draw()
{
    this->window->draw(*rectangleShape);
}