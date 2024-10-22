#include "2d.h"
#include <iostream>

double Type2d::getDistance(const TypeBase &p) const {
    const Type2d & p2d = static_cast<const Type2d &>(p);
    std::cout << "1" << p2d.d;
    return 0.0;
}
