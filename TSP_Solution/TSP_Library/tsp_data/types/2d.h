#pragma once
#include <numbers>    // C++20 just doesn't work with DPC++??
#include <cmath>
#include "type_base.h"

#ifndef M_PI
constexpr double M_PI = 3.14159265358979323846;     // HOW IS THERE NO PI IN C++ STANDARD LIBRARY!?
#endif


class Type2d : public TypeBase {
public:
    // Constructor
    Type2d() : TypeBase(P2DEFAULT) {}
    Type2d(const Point2D& point) : TypeBase(point) {}
    Type2d(GenerationType type, const Square& size, std::mt19937& seed) : TypeBase(generateRandomCities(type, size, seed)) {}

    // Methods
    inline double getDistance(const TypeBase& p) const override {
        const Point2D& point = static_cast<const Type2d&>(p).m_point;
        return std::sqrt(pow(m_point.x - point.x, 2) + pow(m_point.y - point.y, 2)); // Euclidean distance
    }

  //  inline double getDistance(const TypeBase* p) const override {
		//const auto& point = static_cast<const Type2d*>(p)->m_point;
        ////return std::sqrt(pow(m_point.x - point.x, 2) + pow(m_point.y - point.y, 2)); // Euclidean distance
  //  }

    inline bool contains(const Square& s) const override{
        return s.contains(m_point);
    }

	// TODO: Generation code should be apart of Point2D code
    Point2D rectangleGen(const GenerationType type, const Square& size, std::mt19937& seed) const override {
        std::uniform_real_distribution<double> x_rnd(0, size.width);
        std::uniform_real_distribution<double> y_rnd(0, size.height);
        return Point2D(x_rnd(seed), y_rnd(seed));
    }

    Point2D circleGen(const GenerationType type, const Square& size, std::mt19937& seed) const override {
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
        return Point2D(radius * cos(angle), radius * sin(angle)); // Turns Polar coordinates into Cartesian
    }
};

