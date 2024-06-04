#include "CircularArc.h"
//#include "IDataProvider.h"

CircularArc::CircularArc(void) :
    BaseObject(CREATE_CIRCULAR_ARC), m_center(new Point2d({ 0,0 })), m_radius(0), m_start_Angle(0), m_end_Angle(0)
{}

CircularArc::CircularArc(const Point2d& center, const double radius, const double start_Angle, const double end_Angle) :
    BaseObject(CREATE_CIRCULAR_ARC), m_center(new Point2d(center)), m_radius(radius), m_start_Angle(start_Angle), m_end_Angle(end_Angle)
{}

CircularArc::~CircularArc(void)
{
    delete m_center;
}

void CircularArc::set_CircularArc_Center(Point2d& center)
{
    *m_center = center;
}

void CircularArc::set_CircularArc_Radius(const double radius)
{
    m_radius = radius;
}

void CircularArc::set_CircularArc_Start_Angle(const double start_Angle)
{
    m_start_Angle = start_Angle;
}

void CircularArc::set_CircularArc_End_Angle(const double end_Angle)
{
    m_end_Angle = end_Angle;
}


Point2d* CircularArc::get_CircularArc_Center() const
{
    return m_center;
}

double CircularArc::get_CircularArc_Radius() const
{
    return m_radius;
}

double CircularArc::get_CircularArc_Start_Angle() const
{
    return m_start_Angle;
}

double CircularArc::get_CircularArc_End_Angle() const
{
    return m_end_Angle;
}

void CircularArc::draw()
{
    std::cout << "Circular Arc:" << std::endl;
    std::cout << "Center: (" << m_center->x() << ", " << m_center->y() << ")" << std::endl;
    std::cout << "Radius: " << m_radius << std::endl;
    std::cout << "Start Angle: " << m_start_Angle << ", End Angle: " << m_end_Angle << std::endl;
}

void CircularArc::serialize(IDataProvider::IDataReader* dr) const
{
    static constexpr int CIRCULAR_ARC_SIZE = 5;
    //write object size
    dr->wrInt(CIRCULAR_ARC_SIZE);
    //write center
    dr->wrDouble(m_center->x()); dr->wrDouble(m_center->y());
    //write radius
    dr->wrDouble(m_radius);
    //write Angles
    dr->wrDouble(m_start_Angle);  dr->wrDouble(m_end_Angle);
}

void CircularArc::deserialize(IDataProvider::IDataReader* dr, int size)
{
    Point2d point(dr->rdDouble(--size), dr->rdDouble(--size));
    this->set_CircularArc_Center(point);

    this->set_CircularArc_Radius(dr->rdDouble(--size));

    this->set_CircularArc_Start_Angle(dr->rdDouble(--size));
    this->set_CircularArc_End_Angle(dr->rdDouble(--size));
}

BoundingBox CircularArc::AABB() const //не перевіряв чи коректно працює
{
    double min_x = m_center->x() - m_radius;
    double max_x = m_center->x() + m_radius;
    double min_y = m_center->y() - m_radius;
    double max_y = m_center->y() + m_radius;

    // Обчислюємо границі за кутами
    if (m_start_Angle != m_end_Angle) {
        double start_x = m_center->x() + m_radius * cos(m_start_Angle);
        double start_y = m_center->y() + m_radius * sin(m_start_Angle);
        double end_x = m_center->x() + m_radius * cos(m_end_Angle);
        double end_y = m_center->y() + m_radius * sin(m_end_Angle);

        min_x = std::min({ min_x, start_x, end_x });
        max_x = std::max({ max_x, start_x, end_x });
        min_y = std::min({ min_y, start_y, end_y });
        max_y = std::max({ max_y, start_y, end_y });
    }


    // Создайте и верните объект BoundingBox
    return BoundingBox(Point2d(min_x, min_y), Point2d(max_x, max_y));
}



