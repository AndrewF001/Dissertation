#include "Data_2d.h"
#include <iostream>

double Data_2d::getDistance(const Data_Base &p) const {
    const Data_2d & p2d = static_cast<const Data_2d &>(p);
    std::cout << "1" << p2d.d;
    return 0.0;
}
