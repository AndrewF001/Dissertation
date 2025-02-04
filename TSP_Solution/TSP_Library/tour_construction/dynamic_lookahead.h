#pragma once
#include "construction_base.h"
#include "convex_hull.h"
#include "../tsp_data/tsp_data_template.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class DynamicLookahead : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	DynamicLookahead(const size_t depth) : ConstructionBase<TSPType, Size, Caching, Partitioning>("DynamicLookahead"), m_max_depth(depth) {
#ifdef _DEBUG
		if (depth == 0)
			throw std::invalid_argument("Depth must be greater than 0");
#endif
	};
	~DynamicLookahead() = default;

	void _constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		data.setCityPos(0, 0);	// Randomly select the first city

		dynamicLookaheadInsertion(data, m_max_depth);
	};

	static size_t optimalDepth(size_t size, size_t max_depth) {
		size_t optimal = (size_t)std::round(1.2 * std::log(size) - 1.6952);

		if (optimal == 0)
			optimal = 1;
		
		return std::min(optimal, max_depth);
	}

	static void dynamicLookaheadInsertion(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data, size_t max_depth) {
		const size_t additions = Size - data.getRouteSize();
		for (size_t i = additions; i > 0; i--) {
			auto [closest_point, route_position] = StaticLookahead<TSPType, Size, Caching, Partitioning>::FindClosestPoints(data, optimalDepth(i, max_depth));
			data.setCityPos(closest_point, route_position + 1);
		}
	}

private:
	const size_t m_max_depth;
};