#pragma once


#include "BaseObject.h"


#include <vector>


class Unknown : public BaseObject {

public:
	Unknown(const int m_id);
	virtual ~Unknown(void);

	bool push_back_Data(const double d);

	//може видавати помилку читання THROW_ERR
	double get_Data(const int num) const;

	virtual void showAll() override {
		std::cout << "Unknown object with ID: " << BaseObject::p_id_Obj << std::endl;
		std::cout << "Data:" << std::endl;
		for (int i = 0; i < m_size; ++i) {
			std::cout << "  " << m_data[i];
		}
		std::cout << std::endl;
	}

	virtual void deserialize(DataProvider& dp, int size) override;

	

private:
	virtual BoundingBox AABB() const override; // =0 не можна бо клас стане абстрактним

	int m_size;
	std::vector<double> m_data;

};

