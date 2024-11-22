#pragma once
#include "../tsp_data/tsp_data_template.h"


template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class ConstructionBase {
public:
	ConstructionBase() {};
	virtual ~ConstructionBase() = default;

	virtual void constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& m_data_ref) = 0;
};
