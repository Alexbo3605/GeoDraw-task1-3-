#include "Rectangle.h"

Rectangle::Rectangle(void) :
	BaseObject(CREATE_RECTANGLE), m_Top_Left_Point(new Point2d({ 0,0 })), m_Bottom_Right_Point(new Point2d({ 0,0 }))
{}

Rectangle::Rectangle(const Point2d& top_Left_Point, const Point2d& bottom_Right_Point) :
	BaseObject(CREATE_RECTANGLE), m_Top_Left_Point(new Point2d(top_Left_Point)), m_Bottom_Right_Point(new Point2d(bottom_Right_Point))
{}

Rectangle::~Rectangle(void)
{
	std::cout << "~Rectangle { " << m_Top_Left_Point << " " << m_Bottom_Right_Point << " }" << std::endl;
	delete m_Top_Left_Point;
	delete m_Bottom_Right_Point;
}

void Rectangle::set_Rectangle_Top_Left_Point(Point2d& point)
{
	*m_Top_Left_Point = point;
}

void Rectangle::set_Rectangle_Bottom_Right_Point(Point2d& point)
{
	*m_Bottom_Right_Point = point;
}

Point2d* Rectangle::get_Rectangle_Top_Left_Point() const
{
	return m_Top_Left_Point;
}

Point2d* Rectangle::get_Rectangle_Bottom_Right_Point() const
{
	return m_Bottom_Right_Point;
}

void Rectangle::deserialize(DataProvider& dp, int size) //скоріш за все не працює через * короче зроз
{
	Point2d bottom_Right_Point{ dp.rdDouble(--size), dp.rdDouble(--size) };
	this->set_Rectangle_Bottom_Right_Point(bottom_Right_Point);
	
	Point2d top_Left_Point { dp.rdDouble(--size), dp.rdDouble(--size) };
	this->set_Rectangle_Top_Left_Point(top_Left_Point);

}

BoundingBox Rectangle::AABB() const
{
	return BoundingBox( Point2d( m_Top_Left_Point->x(), m_Top_Left_Point->y()),
					    Point2d( m_Bottom_Right_Point->x(), m_Bottom_Right_Point->y()));
}
