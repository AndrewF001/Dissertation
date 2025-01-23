#pragma once
#include "construction_base.h"
#include "convex_hull.h"
#include "../tsp_data/tsp_data_template.h"
#include "static_lookahead.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class StaticLookaheadConvexHull : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	StaticLookaheadConvexHull(const size_t depth) : ConstructionBase<TSPType, Size, Caching, Partitioning>("StaticLookaheadConvexHullInsertion"), m_depth(depth) {
#ifdef _DEBUG
		if (depth == 0)
			throw std::invalid_argument("Depth must be greater than 0");
#endif
	};
	~StaticLookaheadConvexHull() = default;

	void _constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		ConvexHull<TSPType, Size, Caching, Partitioning>::runSingle(data);

		StaticLookahead<TSPType, Size, Caching, Partitioning>::lookaheadInsertion(data, m_depth);
	};

private:
	const size_t m_depth;
};