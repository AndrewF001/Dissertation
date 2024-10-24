#pragma once
#include "type_base.h"

class Type2d : public TypeBase {
public:
	// Constructor
	Type2d(unsigned int id, Point3D point);
	Type2d(unsigned int id, GenerationType type, const Cube &size, std::mt19937 &seed);
	~Type2d() = default;
	
	const Point2D m_point;

	// Methods
	virtual double getDistance(const TypeBase &p) const;
	virtual bool contains(const Cube &s) const;
	virtual Point3D rectangleGen(const GenerationType type, const Cube &size, std::mt19937 &seed) const;
	virtual Point3D circleGen(const GenerationType type, const Cube &size, std::mt19937 &seed) const;
};

