#pragma once


#include "Unknown.h"
#include "Rectangle.h"
#include "Polyline.h"
#include "Polygon.h"
#include "CircularArc.h"
#include "Circle.h"

class  ObjectFactory {
public:

    /*
    num == 1 : CREATE_RECT
    num == 2 : CREATE_CIRCLE
    num == 4 : CREATE_CIRCULAR_ARC
    num == 5 : CREATE_POLYGON
    num == 6 : CREATE_POLYLINE
    */
    static BaseObject* factory(const int num);
};