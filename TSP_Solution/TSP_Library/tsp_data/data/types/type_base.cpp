#include "type_base.h"

Point3D TypeBase::generateRandomCities(const GenerationType type, const Cube &size, std::mt19937 &seed) const {
	switch(type) {
		case GenerationType::Rectangle:
			return rectangleGen(type, size, seed);
		case GenerationType::Circle:
			return circleGen(type, size, seed);
		case GenerationType::AreaCode:
			std::exit(101); // TODO: Not implemented
			return Point3D();
	}
	// Not possible to reach this point
	return Point3D();
}
