#pragma once
#include "../tsp_data/tsp_data_template.h"

enum class ContructionType {
	LookaheadConvexHull,
	NearestNeighbour
};

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class ConstructionBase {
public:
	//ConstructionBase(TspDataTemplate<TSPType, Size, Caching, Partitioning>& ref) : m_data_ref(ref) {};
	ConstructionBase() {};
	virtual ~ConstructionBase() = default;

	virtual void constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& m_data_ref) = 0;

protected:
	//TspDataTemplate<TSPType, Size, Caching, Partitioning>& m_data_ref;
};

