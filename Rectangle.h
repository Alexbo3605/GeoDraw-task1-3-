#pragma once

#include "BaseObject.h"

//#include "Point2d.h"

//#include "ObjectFactory.h"

class Rectangle : public BaseObject {

public:
	Rectangle(void);
	Rectangle(const Point2d& m_Top_Left_Point, const Point2d& m_Bottom_Right_Point);
	virtual ~Rectangle(void);


	Point2d* get_Rectangle_Top_Left_Point() const;
	Point2d* get_Rectangle_Bottom_Right_Point() const;

	virtual void showAll() override {
		// Виведення інформації про прямокутник
		std::cout << "Rectangle:" << std::endl;
		std::cout << "Top left corner: (" << m_Top_Left_Point->x() << ", " << m_Top_Left_Point->y() << ")" << std::endl;
		std::cout << "Bottom right corner: (" << m_Bottom_Right_Point->x() << ", " << m_Bottom_Right_Point->y() << ")" << std::endl;
	}

	virtual void deserialize(DataProvider& dp, int size) override;

	virtual BoundingBox AABB() const override;

private:

	void set_Rectangle_Top_Left_Point(Point2d& point);
	void set_Rectangle_Bottom_Right_Point(Point2d& point);

	Point2d* m_Top_Left_Point;
	Point2d* m_Bottom_Right_Point;

};