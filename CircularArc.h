#pragma once

#include "BaseObject.h"
//#include "IDataProvider.h"
//#include "ArrayDataProvider.h"
//#include "FileDataProvider.h"

class CircularArc : public BaseObject {
public:
	CircularArc(void);
	CircularArc(const Point2d& m_center, const double m_radius, const double m_start_Angle, const double m_end_Angle);
	virtual~CircularArc(void);

	Point2d* get_CircularArc_Center() const;
	double get_CircularArc_Radius() const;
	double get_CircularArc_Start_Angle() const;
	double get_CircularArc_End_Angle() const;

	virtual void showAll() override {
		std::cout << "Circular Arc:" << std::endl;
		std::cout << "Center: (" << m_center->x() << ", " << m_center->y() << ")" << std::endl;
		std::cout << "Radius: " << m_radius << std::endl;
		std::cout << "Start Angle: " << m_start_Angle << ", End Angle: " << m_end_Angle << std::endl;
	}
	virtual void serialize(IDataProvider::IDataReader* dr) const override;
	virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

	virtual BoundingBox AABB() const override;

private:
	void set_CircularArc_Center(Point2d& center);
	void set_CircularArc_Radius(const double radius);
	void set_CircularArc_Start_Angle(const double start_Angle);
	void set_CircularArc_End_Angle(const double end_Angle);

	Point2d* m_center;
	double m_radius;
	double m_start_Angle;
	double m_end_Angle;
};




