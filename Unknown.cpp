#include "Unknown.h"


Unknown::Unknown(const int id) : BaseObject(id), m_size(0)
{}

Unknown::~Unknown(void)
{}

bool Unknown::push_back_Data(const double d)
{
	m_size++;
	m_data.push_back(d);
	return true;
}

double Unknown::get_Data(const int num) const
{
	if (num < m_size) {
		return m_data[num];
	}
	return THROW_ERR;
}

void Unknown::deserialize(DataProvider& dp, int size)
{
	int count = size;
	for (int i = 0; i < count; i++)
	{
		this->push_back_Data(dp.rdDouble(--size));
	}
}

BoundingBox Unknown::AABB() const
{
	return BoundingBox( Point2d{ 0,0 },  Point2d{ 0, 0 });
}
