#pragma once

#include "BaseObject.h"
//#include "BaseObject.h"
//#include "IDataProvider.h"
//#include "ArrayDataProvider.h"
//#include "FileDataProvider.h"
#include <vector>
class Unknown : public BaseObject {

public:
	Unknown(const int m_id);
	virtual ~Unknown(void);

	void push_back_Data(const double d);

	//may throw a read error THROW_ERR
	double get_Data(const int num) const;

	virtual void draw() override;

	virtual void serialize(IDataProvider::IDataReader* dr) const override;
	virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

private:
	virtual BoundingBox AABB() const override; // =0 impossible because the class will become abstract

	int m_size;
	std::vector<double> m_data;
};

