#pragma once
#include "Base_Sources.h"

template <class TSPType, CachingType Caching, class Partitioning>
class T_TSP {

public:
	T_TSP() = default;
	T_TSP_Data<TSPType,Caching, Partitioning> t;
};
