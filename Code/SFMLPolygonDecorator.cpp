#include "SFMLPolygonDecorator.h"


SFMLPolygonDecorator::SFMLPolygonDecorator(Polygon& pl, sf::RenderWindow* window) 
    : polygon(pl), window(window)
{
    polygonShape = new sf::ConvexShape();
    convertPointsToShape();
}

SFMLPolygonDecorator::~SFMLPolygonDecorator()
{
    delete polygonShape;
}

BoundingBox SFMLPolygonDecorator::AABB() const
{
     return polygon.AABB();
}

void SFMLPolygonDecorator::serialize(IDataProvider::IDataReader* dr) const
{
    polygon.serialize(dr);
}

void SFMLPolygonDecorator::deserialize(IDataProvider::IDataReader* dr, int size)
{
    polygon.deserialize(dr, size);
}


void SFMLPolygonDecorator::convertPointsToShape()
{
    
    size_t size = polygon.get_Size();

    if (size < 3) {
        return; 
    }

    polygonShape->setPointCount(size);

    //перетворення Point2d у Vector2f
    for (size_t i = 0; i < size; ++i) {
        Point2d point = *polygon.get_Point(i);
        polygonShape->setPoint(i, sf::Vector2f(point.x(), point.y()));
    }

    polygonShape->setFillColor(sf::Color::White);
}

void SFMLPolygonDecorator::draw()
{
    this->window->draw(*polygonShape);
}
