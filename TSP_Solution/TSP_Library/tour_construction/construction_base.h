#pragma once
#include "../tsp_data/tsp_data_template.h"

enum class ContructionType {
	LookaheadConvexHull,
	NearestNeighbour
};

template<class TSPType, size_t Size, CachingTypes Caching, class Partitioning>
class ConstructionBase {
public:
	ConstructionBase(TspDataTemplate<TSPType, Size, Caching, Partitioning>& ref) : m_data_ref(ref) {};
	~ConstructionBase() = default;

	virtual void constructTour() = 0;

protected:
	TspDataTemplate<TSPType, Size, Caching, Partitioning>& m_data_ref;
};

