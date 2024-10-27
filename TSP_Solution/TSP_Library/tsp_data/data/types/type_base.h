#pragma once
#include <random>
#include "../tsp_constructs.h"
class TypeBase {
public: 
	// Constructor
	TypeBase(const unsigned int id, const Point3D p) : m_id(id) {};
	TypeBase(const unsigned int id, const GenerationType type, const Cube& size, std::mt19937& seed) : m_id(id) {};
	virtual ~TypeBase() = default;

	// ID
	const unsigned int m_id;

	// Methods
	virtual double getDistance(const TypeBase& p) const = 0;
	virtual bool contains(const Cube &s) const = 0;
	Point3D generateRandomCities(const GenerationType type, const Cube &size, std::mt19937 &seed) const;
	virtual Point3D rectangleGen(const GenerationType type, const Cube &size, std::mt19937 &seed) const = 0;
	virtual Point3D circleGen(const GenerationType type, const Cube &size, std::mt19937 &seed) const = 0;
};

