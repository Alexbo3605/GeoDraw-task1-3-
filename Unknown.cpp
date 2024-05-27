#include "Unknown.h"


Unknown::Unknown(const int id) : BaseObject(id), m_size(0)
{}

Unknown::~Unknown(void)
{}

void Unknown::push_back_Data(const double d)
{
	m_size++;
	m_data.push_back(d);
}

double Unknown::get_Data(const int num) const
{
	if (num < m_size) {
		return m_data[num];
	}
	return THROW_ERR;
}

void Unknown::serialize(IDataProvider::IDataReader* dr) const
{
	//write object size
	dr->wrInt(m_size);

	//write data
	for (size_t i = 0; i < m_size; i++)
	{
		dr->wrDouble(m_data[i]);
	}
}

void Unknown::deserialize(IDataProvider::IDataReader* dr, int size)
{
	int count = size;

	for (size_t i = 0; i < count; i++)
	{
		this->push_back_Data(dr->rdDouble(--size));
	}
}

BoundingBox Unknown::AABB() const
{
	return BoundingBox(Point2d{ 0,0 }, Point2d{ 0, 0 });
}
