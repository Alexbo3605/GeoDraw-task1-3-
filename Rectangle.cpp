#include "Rectangle.h"

Rectangle::Rectangle(void) :
	BaseObject(CREATE_RECTANGLE), m_Top_Left_Point(new Point2d({ 0,0 })), m_Bottom_Right_Point(new Point2d({ 0,0 }))
{}

Rectangle::Rectangle(const Point2d& top_Left_Point, const Point2d& bottom_Right_Point) :
	BaseObject(CREATE_RECTANGLE), m_Top_Left_Point(new Point2d(top_Left_Point)), m_Bottom_Right_Point(new Point2d(bottom_Right_Point))
{}

Rectangle::~Rectangle(void)
{
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

void Rectangle::serialize(IDataProvider::IDataReader* dr) const
{
	//write object size
	dr->wrInt(RECTANGLE_SIZE);
	//write Top_Left_Point
	dr->wrDouble(m_Top_Left_Point->x()); dr->wrDouble(m_Top_Left_Point->y());
	//write Bottom_Right_Point
	dr->wrDouble(m_Bottom_Right_Point->x()); dr->wrDouble(m_Bottom_Right_Point->y());
}

void Rectangle::deserialize(IDataProvider::IDataReader* dr, int size) //скоріш за все не працює через * короче зроз
{
	Point2d bottom_Right_Point{ dr->rdDouble(--size), dr->rdDouble(--size) };
	this->set_Rectangle_Bottom_Right_Point(bottom_Right_Point);

	Point2d top_Left_Point{ dr->rdDouble(--size), dr->rdDouble(--size) };
	this->set_Rectangle_Top_Left_Point(top_Left_Point);
}

BoundingBox Rectangle::AABB() const
{
	return BoundingBox(Point2d(m_Top_Left_Point->x(), m_Top_Left_Point->y()),
		Point2d(m_Bottom_Right_Point->x(), m_Bottom_Right_Point->y()));
}
