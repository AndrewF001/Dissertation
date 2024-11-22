#pragma once
#include <random>
#include "../tsp_constructs.h"


class TypeBase {
public: 
	// Constructor
	TypeBase() : m_point(P2DEFAULT){};
	TypeBase(const Point2D& p) : m_point(p) {};
	TypeBase(const GenerationType type, const Square& size, std::mt19937& seed) {};
	virtual ~TypeBase() = default;


	// ID
	//const size_t m_id;	

	// Point Methods
	inline const Point2D& getPoint() const { return m_point; };
	inline virtual double getDistance(const TypeBase& p) const = 0;
	inline virtual double getDistance(const TypeBase* p) const = 0;
	//inline virtual double getDistance(const TypeBase* p) const = 0;
	//inline double getDistance(const TypeBase& p1, const TypeBase& p2) const {	return getDistance(p1) + getDistance(p2);	};
	//inline double getDistance(const TypeBase* p1, const TypeBase* p2) const {	return getDistance(p1) + getDistance(p2);	};
	//inline double calcDeivation(const TypeBase& p1, const TypeBase& p2) const { return getDistance(p1, p2) - p1.getDistance(p2); };
	//inline double calcDeivation(const TypeBase* p1, const TypeBase* p2) const { return getDistance(p1, p2) - p1->getDistance(p2); };
	inline virtual bool contains(const Square &s) const = 0;
	virtual Point2D rectangleGen(const GenerationType type, const Square &size, std::mt19937 &seed) const = 0;
	virtual Point2D circleGen(const GenerationType type, const Square &size, std::mt19937 &seed) const = 0;

	// Route Methods
	inline const cityID getRoutePosition() const { return m_route_position; };
	inline void setRoutePosition(const size_t pos) { m_route_position = pos; };
	inline void resetRoutePosition() { m_route_position = SIZE_MAX; };
	inline void incrementRoutePosition() { m_route_position++; };
	inline void decrementRoutePosition() { m_route_position--; };
	inline bool isInRoute() const { return m_route_position != SIZE_MAX; };

	// Generation
	Point2D generateRandomCities(const GenerationType type, const Square &size, std::mt19937 &seed) const {
		switch (type) {
			case GenerationType::rectangle:
				return rectangleGen(type, size, seed);
			case GenerationType::circle:
				return circleGen(type, size, seed);
			case GenerationType::areaCode:
				std::exit(101); // TODO: Not implemented
				return Point2D();
		}
		// Not possible to reach this point
		return Point2D();
	};

protected:
	Point2D m_point;	// TODO: This should be const
private:
	cityID m_route_position = SIZE_MAX;
};

