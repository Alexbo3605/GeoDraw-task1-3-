#include "Polyline.h"
//#include "IDataProvider.h"

Polyline::Polyline(void)
	: BaseObject(CREATE_POLYLINE), m_size(0), m_points()
{}

Polyline::Polyline(const int size, const std::vector<Point2d*>& points)
	: BaseObject(CREATE_POLYLINE), m_size(size), m_points(points)
{}

Polyline::~Polyline(void)
{
	for (Point2d* i : m_points) {
		delete i;
	}
	m_points.clear();
}

bool Polyline::push_back_Point(Point2d& point)
{
	m_points.push_back(&point);
	m_size++;
	return true;
}

Point2d* Polyline::get_Point(const int num) const
{
	if (num < m_size) {
		return m_points[num];
	}
	return nullptr;

}

int Polyline::get_Size() const
{
	return m_size;
}

void Polyline::draw()
{
	std::cout << "Polyline:" << std::endl;
	std::cout << "Number of vertices: " << m_size << std::endl;
	for (size_t i = 0; i < m_size; ++i) {
		std::cout << "Vertex " << i + 1 << ": (" << m_points[i]->x() << ", " << m_points[i]->y() << ")" << std::endl;
	}
}

void Polyline::serialize(IDataProvider::IDataReader* dr) const
{
	//write object size
	dr->wrInt(m_size * 2);

	//write m_size points
	for (size_t i = 0; i < m_size; i++)
	{
		dr->wrDouble(m_points[i]->x());
		dr->wrDouble(m_points[i]->y());
	}
}

void Polyline::deserialize(IDataProvider::IDataReader* dr, int size)
{
	int pointCount = size / 2;

	for (size_t i = 0; i < pointCount; i++)
	{
		Point2d* point = new Point2d{ dr->rdDouble(--size), dr->rdDouble(--size) };
		this->push_back_Point(*point);

	}
}

BoundingBox Polyline::AABB() const
{
	if (m_size == 0) {
		return BoundingBox(Point2d(0, 0), Point2d(0, 0));
	}

	double min_x = std::numeric_limits<double>::max();
	double max_x = std::numeric_limits<double>::lowest();
	double min_y = std::numeric_limits<double>::max();
	double max_y = std::numeric_limits<double>::lowest();

	for (const auto& point : m_points) {
		min_x = std::min(min_x, point->x());
		max_x = std::max(max_x, point->x());
		min_y = std::min(min_y, point->y());
		max_y = std::max(max_y, point->y());
	}

	return BoundingBox(Point2d(min_x, max_y), Point2d(max_x, min_y));
}

