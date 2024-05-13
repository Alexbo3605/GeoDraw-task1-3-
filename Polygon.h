#pragma once

#include "BaseObject.h"

//#include "Point2d.h"

#include <vector>

//#include "ObjectFactory.h"

class Polygon : public BaseObject {

public:
	Polygon(void);
	Polygon(const int m_size, const std::vector<Point2d*>& Points);
	virtual ~Polygon(void);

	bool push_back_Point(Point2d& point);

	Point2d* get_Point(const int num) const;
	int get_Size() const;

	virtual void showAll() override {
		// Виведення інформації про багатокутник
		std::cout << "Polygon:" << std::endl;
		std::cout << "Number of vertices: " << m_size << std::endl;
		for (int i = 0; i < m_size; ++i) {
			std::cout << "Vertex " << i + 1 << ": (" << m_points[i]->x() << ", " << m_points[i]->y() << ")" << std::endl;
		}
	}

	virtual void deserialize(DataProvider& dp, int size) override;

	virtual BoundingBox AABB() const override;

private:

	int m_size;
	std::vector<Point2d*> m_points;


};





