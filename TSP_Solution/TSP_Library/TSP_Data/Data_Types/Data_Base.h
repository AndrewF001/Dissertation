#pragma once
#include "../TSP_Data/TSP_Types.h"

class Data_Base {
public: 
	// Constructor
	Data_Base(unsigned int i) : m_id(i) {};
	~Data_Base() = default;

	// ID
	const unsigned int m_id;

	// Methods
	virtual double getDistance(const Data_Base& p) = 0;
};

