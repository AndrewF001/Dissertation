#pragma once
#include "Data_Base.h"
#include <iostream>

class Data_2d : public Data_Base {
public:
	// Constructor
	Data_2d(unsigned int i) : Data_Base(i) {};
	~Data_2d() = default;
	double d = 4;
	// Methods
	double getDistance(const Data_Base &p) const;
};

