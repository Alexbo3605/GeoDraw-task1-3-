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

	virtual void showAll() override {
		std::cout << "Unknown object with ID: " << BaseObject::p_id_Obj << std::endl;
		std::cout << "Data:" << std::endl;
		for (size_t i = 0; i < m_size; ++i) {
			std::cout << "  " << m_data[i];
		}
		std::cout << std::endl;
	}

	virtual void serialize(IDataProvider::IDataReader* dr) const override;
	virtual void deserialize(IDataProvider::IDataReader* dr, int size) override;

private:
	virtual BoundingBox AABB() const override; // =0 impossible because the class will become abstract

	int m_size;
	std::vector<double> m_data;
};

