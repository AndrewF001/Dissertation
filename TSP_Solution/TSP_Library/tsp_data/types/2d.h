#pragma once
#include "type_base.h"

class Type2d : public TypeBase {
public:
	// Constructor
	Type2d();
	Type2d(Point3D const& point);
	Type2d(GenerationTypes type, const Cube &size, std::mt19937 &seed);
	~Type2d() = default;

	Point2D m_point;	// TODO: This should be const

	// Methods
	inline double getDistance(const TypeBase &p) const override;
	inline bool contains(const Cube &s) const override;
	Point3D rectangleGen(const GenerationTypes type, const Cube &size, std::mt19937 &seed) const override;
	Point3D circleGen(const GenerationTypes type, const Cube &size, std::mt19937 &seed) const override;
};

