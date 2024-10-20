#pragma once
#include "Data_Base.h"
#include <iostream>
class Data_2d : public Data_Base {
public:
	// Constructor
	Data_2d(unsigned int i) : Data_Base(i) {};
	~Data_2d() = default;

	// Methods
	double getDistance(const Data_Base &p) {
		std::cout << "1";
		return 0;
	};
	//virtual double getDistance(const Data_2d& p);
};

