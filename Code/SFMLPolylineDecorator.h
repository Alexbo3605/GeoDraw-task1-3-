#pragma once

#include "Polyline.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

class SFMLPolylineDecorator : public BaseObject {
private:
    void convertPointsToVertexArray();
    Polyline polyline;
    sf::VertexArray polylineShape;
    sf::RenderWindow* window;
public:
    SFMLPolylineDecorator(Polyline &pl, sf::RenderWindow* window);
    virtual ~SFMLPolylineDecorator();
 
    virtual BoundingBox AABB() const override;
    virtual void serialize(IDataProvider::IDataReader* dr) const override;
    virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;
    
    virtual void draw() override;
};