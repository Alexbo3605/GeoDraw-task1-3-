#pragma once

#include "CircularArc.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

#include <cmath>


class SFMLCircularArcDecorator : public BaseObject {
private:
    void convertPointsToArc();
    CircularArc arc;
    sf::VertexArray arcShape;
    sf::RenderWindow* window;
public:
    SFMLCircularArcDecorator(CircularArc& ca, sf::RenderWindow* window);
    virtual ~SFMLCircularArcDecorator();

    virtual BoundingBox AABB() const override;
    virtual void serialize(IDataProvider::IDataReader* dr) const override;
    virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

    virtual void draw() override;
};
