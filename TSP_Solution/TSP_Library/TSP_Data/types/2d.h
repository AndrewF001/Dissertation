#pragma once
#include "type_base.h"
#include <iostream>

class Type2d : public TypeBase {
public:
	// Constructor
	Type2d(unsigned int i) : TypeBase(i) {};
	~Type2d() = default;
	double d = 4;
	// Methods
	virtual double getDistance(const TypeBase &p) const;
};

