#pragma once

#include "ObjectFactory.h"
#include "SFMLCircleDecorator.h"
#include "SFMLCircularArcDecorator.h"
#include "SFMLPolygonDecorator.h"
#include "SFMLPolylineDecorator.h"
#include "SFMLRectangleDecorator.h"

class SFMLObjectsFactory {

public:

	static std::unique_ptr<BaseObject> factory(const BaseObject* obj);

};