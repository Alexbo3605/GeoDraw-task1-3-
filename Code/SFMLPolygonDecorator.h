#pragma once

#include "Polygon.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

class SFMLPolygonDecorator : public BaseObject {
private:
    void convertPointsToShape();
    Polygon polygon;
    sf::ConvexShape* polygonShape;
    sf::RenderWindow* window;
public:
    SFMLPolygonDecorator(Polygon& pg, sf::RenderWindow* window);
    virtual ~SFMLPolygonDecorator();

    virtual BoundingBox AABB() const override;
    virtual void serialize(IDataProvider::IDataReader* dr) const override;
    virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

    virtual void draw() override;
    
};