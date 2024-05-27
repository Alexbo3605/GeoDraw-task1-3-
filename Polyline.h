#pragma once
#include "BaseObject.h"

#include <vector>
class Polyline : public BaseObject {

public:
	Polyline(void);
	Polyline(const int m_size, const std::vector<Point2d*>& Points);
	virtual ~Polyline(void);

	bool push_back_Point(Point2d& point);

	Point2d* get_Point(const int num) const;
	int get_Size() const;

	virtual void showAll() override {
		std::cout << "Polyline:" << std::endl;
		std::cout << "Number of vertices: " << m_size << std::endl;
		for (size_t i = 0; i < m_size; ++i) {
			std::cout << "Vertex " << i + 1 << ": (" << m_points[i]->x() << ", " << m_points[i]->y() << ")" << std::endl;
		}
	}
	virtual void serialize(IDataProvider::IDataReader* dr) const override;
	virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

	virtual BoundingBox AABB() const override;

private:
	int m_size;
	std::vector<Point2d*> m_points;
};



