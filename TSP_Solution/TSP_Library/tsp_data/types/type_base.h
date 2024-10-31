#pragma once
#include <random>
#include "../tsp_constructs.h"
class TypeBase {
public: 
	// Constructor
	TypeBase(){};
	TypeBase(const Point3D& p) {};
	TypeBase(const GenerationTypes type, const Cube& size, std::mt19937& seed){};
	virtual ~TypeBase() = default;

	// ID
	//const size_t m_id;	

	// Methods
	inline virtual double getDistance(const TypeBase& p) const = 0;
	inline virtual bool contains(const Cube &s) const = 0;
	virtual Point3D rectangleGen(const GenerationTypes type, const Cube &size, std::mt19937 &seed) const = 0;
	virtual Point3D circleGen(const GenerationTypes type, const Cube &size, std::mt19937 &seed) const = 0;
	
	Point3D generateRandomCities(const GenerationTypes type, const Cube &size, std::mt19937 &seed) const {
		switch (type) {
		case GenerationTypes::Rectangle:
			return rectangleGen(type, size, seed);
		case GenerationTypes::Circle:
			return circleGen(type, size, seed);
		case GenerationTypes::AreaCode:
			std::exit(101); // TODO: Not implemented
			return Point3D();
		}
		// Not possible to reach this point
		return Point3D();
	};
};

