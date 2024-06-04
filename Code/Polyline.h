#pragma once
#include "BaseObject.h"
//#include "IDataProvider.h"
//#include "ArrayDataProvider.h"
//#include "FileDataProvider.h"

#include <vector>
class Polyline : public BaseObject {

public:
	Polyline(void);
	Polyline(const int m_size, const std::vector<Point2d*>& Points);
	virtual ~Polyline(void);

	bool push_back_Point(Point2d& point);

	Point2d* get_Point(const int num) const;
	int get_Size() const;

	virtual void draw() override;
	virtual void serialize(IDataProvider::IDataReader* dr) const override;
	virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

	virtual BoundingBox AABB() const override;

private:
	int m_size;
	std::vector<Point2d*> m_points;
};



