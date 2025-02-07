#pragma once
#include "construction_base.h"
#include "convex_hull.h"
#include "../tsp_data/tsp_data_template.h"
#include "dynamic_lookahead.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class DynamicLookaheadConvexHull : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	DynamicLookaheadConvexHull(const size_t depth, const DynamicArgs args) : ConstructionBase<TSPType, Size, Caching, Partitioning>("DynamicLookaheadConvexHullInsertion"), m_max_depth(depth), m_args(args) {
#ifdef _DEBUG
		if (depth == 0)
			throw std::invalid_argument("Depth must be greater than 0");
#endif
	};
	~DynamicLookaheadConvexHull() = default;

	void _constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		ConvexHull<TSPType, Size, Caching, Partitioning>::runSingle(data);

		DynamicLookahead<TSPType, Size, Caching, Partitioning>::dynamicLookaheadInsertion(data, m_max_depth, m_args);
	};

private:
	const size_t m_max_depth;
	const DynamicArgs m_args;
};