#pragma once
#include "../tsp_data/data/tsp_data_template.h"

enum class ContructionType {
	LookaheadConvexHull,
	NearestNeighbour
};

template<class TSPType, CachingType Caching, class Partitioning>
class ConstructionBase {
public:
	ConstructionBase(TspDataTemplate<TSPType, Caching, Partitioning>& ref) : m_data_ref(ref) {};
	~ConstructionBase() = default;

	virtual void constructTour() = 0;

protected:
	TspDataTemplate<TSPType, Caching, Partitioning>& m_data_ref;
};

