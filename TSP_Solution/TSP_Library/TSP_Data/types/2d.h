#pragma once
#include "type_base.h"

class Type2d : public TypeBase {
public:
	// Constructor
	Type2d(unsigned int id, Point3D point) : TypeBase(id, point), m_point(point) {};
	~Type2d() = default;
	
	const Point2D m_point;

	// Methods
	virtual double getDistance(const TypeBase &p) const;
	virtual bool contains(const Cube &s) const;
	virtual bool generateRandomCities(const GenerationType type, const int num_cities, const int seed, Cube size) const;
};

