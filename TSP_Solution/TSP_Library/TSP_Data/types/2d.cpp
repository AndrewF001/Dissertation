#include "2d.h"
#include <cmath>

double Type2d::getDistance(const TypeBase &p) const {
    const Type2d & p2d = static_cast<const Type2d &>(p);
    Point2D const &p2 = p2d.m_point;

    return pow(m_point.x - p2.x, 2) + pow(m_point.y - p2.y, 2);
}

bool Type2d::contains(const Cube &s) const {
    return s.contains(m_point);
}

bool Type2d::generateRandomCities(const GenerationType type, const int num_cities, const int seed, Cube size) const {
    return false;
}
