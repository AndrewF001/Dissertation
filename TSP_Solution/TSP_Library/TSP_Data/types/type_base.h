#pragma once
//#include "../data/tsp_constructs.h"

class TypeBase {
public: 
	// Constructor
	TypeBase(unsigned int i) : m_id(i) {};
	virtual ~TypeBase() = default;

	// ID
	const unsigned int m_id;

	// Methods
	virtual double getDistance(const TypeBase& p) const = 0;
};

