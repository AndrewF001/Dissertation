#pragma once
#include <random>
#include "../tsp_constructs.h"

class TypeBase {
public: 
	// Constructor
	TypeBase(){};
	TypeBase(const Point2D& p) {};
	TypeBase(const GenerationType type, const Square& size, std::mt19937& seed){};
	virtual ~TypeBase() = default;

	// ID
	//const size_t m_id;	

	// Methods
	inline virtual double getDistance(const TypeBase& p) const = 0;
	inline virtual bool contains(const Square &s) const = 0;
	virtual Point2D rectangleGen(const GenerationType type, const Square &size, std::mt19937 &seed) const = 0;
	virtual Point2D circleGen(const GenerationType type, const Square &size, std::mt19937 &seed) const = 0;
	
	Point2D generateRandomCities(const GenerationType type, const Square &size, std::mt19937 &seed) const {
		switch (type) {
		case GenerationType::Rectangle:
			return rectangleGen(type, size, seed);
		case GenerationType::Circle:
			return circleGen(type, size, seed);
		case GenerationType::AreaCode:
			std::exit(101); // TODO: Not implemented
			return Point2D();
		}
		// Not possible to reach this point
		return Point2D();
	};
};

