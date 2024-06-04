#include "SFMLPolylineDecorator.h"

SFMLPolylineDecorator::SFMLPolylineDecorator(Polyline &pl, sf::RenderWindow* window) 
    : polyline(pl), polylineShape(sf::LinesStrip), window(window)
{
    convertPointsToVertexArray();
}

SFMLPolylineDecorator::~SFMLPolylineDecorator()
{
}

BoundingBox SFMLPolylineDecorator::AABB() const
{
    return polyline.AABB();
}

void SFMLPolylineDecorator::serialize(IDataProvider::IDataReader* dr) const
{
    polyline.serialize(dr);
}

void SFMLPolylineDecorator::deserialize(IDataProvider::IDataReader* dr, int size)
{
    polyline.deserialize(dr, size);
}


void SFMLPolylineDecorator::convertPointsToVertexArray()
{
    size_t size = polyline.get_Size(); 

    if (size < 2) {
        return;
    }

    polylineShape.resize(size);

    //перетворення Point2d у Vector2f
    for (size_t i = 0; i < size; ++i) {
        Point2d point = *polyline.get_Point(i);
        polylineShape[i].position = sf::Vector2f(point.x(), point.y());
        polylineShape[i].color = sf::Color::White;
    }
}

void SFMLPolylineDecorator::draw()
{
    this->window->draw(polylineShape);
}
