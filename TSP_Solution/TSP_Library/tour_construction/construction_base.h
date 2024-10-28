#pragma once
#include "../tsp_data/data/tsp_data_template.h"

enum class ContructionType {
	LookaheadConvexHull,
	NearestNeighbour
};

template<class TSPType, CachingType Caching, class Partitioning, size_t Size>
class ConstructionBase {
public:
	ConstructionBase(TspDataTemplate<TSPType, Caching, Partitioning, Size>& ref) : m_data_ref(ref) {};
	~ConstructionBase() = default;

	virtual void constructTour() = 0;

protected:
	TspDataTemplate<TSPType, Caching, Partitioning, Size>& m_data_ref;
};

