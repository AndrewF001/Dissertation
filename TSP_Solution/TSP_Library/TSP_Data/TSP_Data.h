#pragma once
#include <vector>
#include "Data_Base.h"
#include "Partitioning/Partitioning_Base.h"

enum CachingType {
	Full,
	Partial,
	None
};

template <class TSPType, CachingType Caching, class Partitioning>
class TSP_Data {
	//static_assert(std::is_base_of<Data_Base, TSPType>::value, "TSPType must be a derived class of TSPType in TSP_Data<T,C,P>");
	//static_assert(std::is_base_of<Partitioning_Base, Partitioning>::value, "Partitioning must be a derived class of Partitioning_Base in TSP_Data<T,C,P>");
public:
	//TSP_Data();
	//~TSP_Data();

private:
	std::vector<TSPType> m_cities;
	std::vector<std::vector<double>> m_cache;
	Partitioning m_partition;
};

