#include "Circle.h"
//#include "IDataProvider.h"

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

void Circle::draw()
{
	std::cout << "Circle:" << std::endl;
	std::cout << "Center: (" << m_center->x() << ", " << m_center->y() << ")" << std::endl;
	std::cout << "Radius: " << m_radius << std::endl;
}

void Circle::serialize(IDataProvider::IDataReader* dr) const
{
	static constexpr int CIRCLE_SIZE = 3;
	//write object size
	dr->wrInt(CIRCLE_SIZE);
	//write center
	dr->wrDouble(m_center->x()); dr->wrDouble(m_center->y());
	//write radius
	dr->wrDouble(m_radius);
}

void Circle::deserialize(IDataProvider::IDataReader* dr, int size)
{
	Point2d point(dr->rdDouble(--size), dr->rdDouble(--size));
	this->set_Circle_Center(point);

	this->set_Circle_Radius(dr->rdDouble(--size));
}

BoundingBox Circle::AABB() const
{
	double min_x = m_center->x() - m_radius;
	double max_x = m_center->x() + m_radius;
	double min_y = m_center->y() - m_radius;
	double max_y = m_center->y() + m_radius;

	return BoundingBox(Point2d(min_x, max_y), Point2d(max_x, min_y));
}


