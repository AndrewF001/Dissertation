#pragma once
#include "construction_base.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class LookaheadConvexHull : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	LookaheadConvexHull(TspDataTemplate<TSPType, Size, Caching, Partitioning>& ref) : ConstructionBase<TSPType, Size, Caching, Partitioning>(ref) {};
	~LookaheadConvexHull() = default;

	void constructTour() override {
		std::cout << "Lookahead Convex Hull\n";
	};
};