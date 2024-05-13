#include "Circle.h"


Circle::Circle(void) 
	: BaseObject(CREATE_CIRCLE), m_center(new Point2d({ 0,0 })), m_radius(0.0)
{}

Circle::Circle(const Point2d& center, const double radius) 
	: BaseObject(CREATE_CIRCLE), m_center(new Point2d(center)), m_radius(radius)
{}

Circle::~Circle(void)
{
	delete m_center;
}

void Circle::set_Circle_Center(Point2d& center)
{
	*m_center = center;
}

void Circle::set_Circle_Radius(const double radius)
{
	m_radius = radius;
}

Point2d* Circle::get_Circle_Center() const
{
	return m_center;
}

double Circle::get_Circle_Radius() const
{
	return m_radius;
}

void Circle::deserialize(DataProvider& dp, int size)
{
	Point2d point(dp.rdDouble(--size), dp.rdDouble(--size));
	this->set_Circle_Center(point);

	this->set_Circle_Radius(dp.rdDouble(--size));

}

BoundingBox Circle::AABB() const
{
	double min_x = m_center->x() - m_radius;
	double max_x = m_center->x() + m_radius;
	double min_y = m_center->y() - m_radius;
	double max_y = m_center->y() + m_radius;

	return BoundingBox(Point2d(min_x, max_y), Point2d(max_x, min_y));
}


