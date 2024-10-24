#pragma once
#include "../data/tsp_constructs.h"

class TypeBase {
public: 
	// Constructor
	TypeBase(unsigned int id, Point3D p) : m_id(id) {};
	virtual ~TypeBase() = default;

	// ID
	const unsigned int m_id;

	// Methods
	virtual double getDistance(const TypeBase& p) const = 0;
	virtual bool contains(const Cube &s) const = 0;
	virtual bool generateRandomCities(const GenerationType type, const int num_cities, const int seed, Cube size) const = 0;
};

