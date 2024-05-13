#include "Point2d.h"

//#include "iostream"

Point2d::Point2d(double xx, double yy) : m_dX(xx), m_dY(yy)
{
}

Point2d::~Point2d(void)
{
	/*std::cout << "~Point2d { " <<m_dX <<" " <<m_dY << " }" << std::endl;*/
}
