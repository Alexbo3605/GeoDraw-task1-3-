#include "BoundingBox.h"

BoundingBox::BoundingBox(const Point2d& top_Left_Point, const Point2d& bottom_Right_Point) :
	m_Top_Left_Point(new Point2d(top_Left_Point)), m_Bottom_Right_Point(new Point2d(bottom_Right_Point))
{}

BoundingBox::~BoundingBox(void)
{
	delete m_Top_Left_Point;
	delete m_Bottom_Right_Point;
}


Point2d* BoundingBox::get_Top_Left_Point() const
{
	return m_Top_Left_Point;
}

Point2d* BoundingBox::get_Bottom_Right_Point() const
{
	return m_Bottom_Right_Point;
}

std::vector<Point2d*> BoundingBox::get_Four_Points() const
{
	/*
		__________
		|P2     P3|
		|		  |
		|		  |
		|P1_____P4|

		m_Top_Left_Point -----> P2

		m_Bottom_Right_Point -> P4
	*/

	std::vector<Point2d*> AABB;

	Point2d* p1 = new Point2d(m_Top_Left_Point->x(), m_Bottom_Right_Point->y());
	Point2d* p3 = new Point2d(m_Top_Left_Point->y(), m_Bottom_Right_Point->x());
	AABB.reserve(4);

	AABB.push_back(p1);
	AABB.push_back(m_Top_Left_Point);
	AABB.push_back(p3);
	AABB.push_back(m_Bottom_Right_Point);

	return AABB;
}
