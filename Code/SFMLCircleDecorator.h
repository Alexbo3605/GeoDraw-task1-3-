#pragma once

#include "Circle.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

class SFMLCircleDecorator : public BaseObject {
private:
    void initializeShape();

    Circle circle;
    sf::CircleShape* circleShape;
    sf::RenderWindow* window;
public:
    SFMLCircleDecorator(Circle& cr, sf::RenderWindow* window);
    virtual ~SFMLCircleDecorator();

    virtual BoundingBox AABB() const override;
    virtual void serialize(IDataProvider::IDataReader* dr) const override;
    virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

    virtual void draw() override;
};

