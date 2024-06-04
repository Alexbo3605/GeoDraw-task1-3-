#pragma once
#include "Point2d.h"

#include <vector>
class BoundingBox {

public:
	BoundingBox(const Point2d& m_Top_Left_Point, const Point2d& m_Bottom_Right_Point);
	~BoundingBox(void);

	Point2d* get_Top_Left_Point() const;
	Point2d* get_Bottom_Right_Point() const;

	std::vector<Point2d*> get_Four_Points() const;

private:
	Point2d* m_Top_Left_Point;
	Point2d* m_Bottom_Right_Point;
};