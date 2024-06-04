#pragma once
#include "BaseObject.h"
//#include "ArrayDataProvider.h"
//#include "FileDataProvider.h"
//#include "BaseObject.h"
//#include "IDataProvider.h"
class Rectangle : public BaseObject {
public:
	Rectangle(void);
	Rectangle(const Point2d& m_Top_Left_Point, const Point2d& m_Bottom_Right_Point);
	virtual ~Rectangle(void);

	Point2d* get_Rectangle_Top_Left_Point() const;
	Point2d* get_Rectangle_Bottom_Right_Point() const;

	virtual void draw() override;

	virtual void serialize(IDataProvider::IDataReader* dr) const override;
	virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

	virtual BoundingBox AABB() const override;

private:
	void set_Rectangle_Top_Left_Point(Point2d& point);
	void set_Rectangle_Bottom_Right_Point(Point2d& point);

	Point2d* m_Top_Left_Point;
	Point2d* m_Bottom_Right_Point;
};