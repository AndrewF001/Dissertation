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

	// Point Methods
	inline virtual double getDistance(const TypeBase& p) const = 0;
	inline double getDistance(const TypeBase& p1, const TypeBase& p2) const {	return getDistance(p1) + getDistance(p2);	};
	inline virtual bool contains(const Square &s) const = 0;
	virtual Point2D rectangleGen(const GenerationType type, const Square &size, std::mt19937 &seed) const = 0;
	virtual Point2D circleGen(const GenerationType type, const Square &size, std::mt19937 &seed) const = 0;

	// Route Methods
	inline size_t getRoutePosition() const { return m_route_position; };
	inline void setRoutePosition(const size_t pos) { m_route_position = pos; };
	inline void incrementRoutePosition() { m_route_position++; };
	inline bool isInRoute() const { return m_route_position != SIZE_MAX; };

	// Generation
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

private:
	cityID m_route_position = SIZE_MAX;
};

