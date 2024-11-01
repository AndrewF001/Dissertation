#pragma once
#include <numbers>    // C++20 just doesn't work with DPC++??
#include <cmath>
#include "2d.h"
#include "type_base.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846     // HOW IS THERE NO PI IN C++ STANDARD LIBRARY!?
#endif


class Type2d : public TypeBase {
public:
	Point2D m_point;	// TODO: This should be const

    // Constructor
    Type2d() : TypeBase(), m_point(P3DEFAULT) {}
    Type2d(const Point3D& point) : TypeBase(point), m_point(point) {}
    Type2d(GenerationType type, const Cube& size, std::mt19937& seed)
        : TypeBase(type, size, seed), m_point(generateRandomCities(type, size, seed)) {}

    // Methods
    // TODO: add pythagorean theorem for distance calculation
    inline double getDistance(const TypeBase& p) const override {
        const Type2d& p2d = static_cast<const Type2d&>(p);
        const Point2D& p2 = p2d.m_point;
        return pow(m_point.x - p2.x, 2) + pow(m_point.y - p2.y, 2); // Euclidean distance as Pythagorean theorem is expensive with no benefit
    }

    inline bool contains(const Cube& s) const override{
        return s.contains(m_point);
    }

    Point3D rectangleGen(const GenerationType type, const Cube& size, std::mt19937& seed) const override {
        std::uniform_real_distribution<double> x_rnd(0, size.width);
        std::uniform_real_distribution<double> y_rnd(0, size.height);
        return Point3D(x_rnd(seed), y_rnd(seed), 0);
    }

    Point3D circleGen(const GenerationType type, const Cube& size, std::mt19937& seed) const override {
        std::uniform_real_distribution<double> angle_rnd(0, M_PI * 2);
        std::uniform_real_distribution<double> radius_rnd;
        if (size.height > size.width) {
            radius_rnd = std::uniform_real_distribution<double>(0, size.width / 2);
        }
        else {
            radius_rnd = std::uniform_real_distribution<double>(0, size.height / 2);
        }
        double angle = angle_rnd(seed);
        double radius = radius_rnd(seed);
        return Point3D(radius * cos(angle), radius * sin(angle), 0); // Turns Polar coordinates into Cartesian
    }
};

