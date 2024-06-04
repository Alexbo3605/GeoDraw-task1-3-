#pragma once

#include "BaseObject.h"
//#include "IDataProvider.h"
//#include "ArrayDataProvider.h"
//#include "FileDataProvider.h"

class Circle : public BaseObject {
public:
	Circle(void);
	Circle(const Point2d& m_center, const double m_radius);
	virtual ~Circle(void);

	Point2d* get_Circle_Center() const;
	double get_Circle_Radius() const;

	virtual void draw() override;
	virtual void serialize(IDataProvider::IDataReader* dr) const override;
	virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

	virtual BoundingBox AABB() const override;

private:
	void set_Circle_Center(Point2d& m_center);
	void set_Circle_Radius(const double m_radius);

	Point2d* m_center;
	double m_radius;
};
