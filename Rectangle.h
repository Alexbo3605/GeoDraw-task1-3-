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

	virtual void showAll() override {
		std::cout << "Rectangle:" << std::endl;
		std::cout << "Top left corner: (" << m_Top_Left_Point->x() << ", " << m_Top_Left_Point->y() << ")" << std::endl;
		std::cout << "Bottom right corner: (" << m_Bottom_Right_Point->x() << ", " << m_Bottom_Right_Point->y() << ")" << std::endl;
	}

	virtual void serialize(IDataProvider::IDataReader* dr) const override;
	virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

	virtual BoundingBox AABB() const override;

private:
	void set_Rectangle_Top_Left_Point(Point2d& point);
	void set_Rectangle_Bottom_Right_Point(Point2d& point);

	Point2d* m_Top_Left_Point;
	Point2d* m_Bottom_Right_Point;
};