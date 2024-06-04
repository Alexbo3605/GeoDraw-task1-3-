#include "SFMLCircularArcDecorator.h"




SFMLCircularArcDecorator::SFMLCircularArcDecorator(CircularArc& ca, sf::RenderWindow* window) 
    : arc(ca), arcShape(sf::LinesStrip), window(window)
{
    convertPointsToArc();
}

SFMLCircularArcDecorator::~SFMLCircularArcDecorator()
{
}

BoundingBox SFMLCircularArcDecorator::AABB() const
{
    return arc.AABB();
}

void SFMLCircularArcDecorator::serialize(IDataProvider::IDataReader* dr) const
{
    arc.serialize(dr);
}

void SFMLCircularArcDecorator::deserialize(IDataProvider::IDataReader* dr, int size)
{
    arc.deserialize(dr, size);
}

void SFMLCircularArcDecorator::convertPointsToArc()
{

    const Point2d center = *arc.get_CircularArc_Center();
    const double radius = arc.get_CircularArc_Radius();
    const double startAngle = arc.get_CircularArc_Start_Angle();
    const double endAngle = arc.get_CircularArc_End_Angle();
    
    //визначаєм кількість точок 
    const double arcLength = radius * (endAngle - startAngle) * 0.2;
    const int numSegments = static_cast<int>(arcLength);
    
    arcShape.clear();
   
    //отримуєм точки
    for (int i = 0; i <= numSegments; ++i) {
        double theta = startAngle + (endAngle - startAngle) * i / numSegments; //кут в радіанах
        double x = center.x() + radius * std::cos(theta);
        double y = center.y() + radius * std::sin(theta);
        arcShape.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::White));
    }
}

void SFMLCircularArcDecorator::draw()
{
    this->window->draw(arcShape);
}



