#pragma once
#include "construction_base.h"
#include "convex_hull.h"
#include "../tsp_data/tsp_data_template.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class LookaheadConvexHull : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	LookaheadConvexHull() : ConstructionBase<TSPType, Size, Caching, Partitioning>() {};
	~LookaheadConvexHull() = default;

	void constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		ConvexHull<TSPType, Size, Caching, Partitioning>::runSingle(data);

		std::cout << "Lookahead Convex Hull\n";
	};
};