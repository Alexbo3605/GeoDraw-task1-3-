#pragma once

#include "Rectangle.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

class SFMLRectangleDecorator : public BaseObject {
private:
    void initializeRectangleShape();
    Rectangle rectangle;
    sf::RectangleShape* rectangleShape;
    sf::RenderWindow* window;
public:
    SFMLRectangleDecorator(Rectangle& rect, sf::RenderWindow* window);
    virtual ~SFMLRectangleDecorator();

    virtual BoundingBox AABB() const override;
    virtual void serialize(IDataProvider::IDataReader* dr) const override;
    virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

    virtual void draw() override;  
};
