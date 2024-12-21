#pragma once
#include "construction_base.h"
#include "convex_hull.h"
#include "../tsp_data/tsp_data_template.h"
#include "shortest_insertion.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class ConvexHullInsertion : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	ConvexHullInsertion() : ConstructionBase<TSPType, Size, Caching, Partitioning>("ConvexHullInsertion") {};
	~ConvexHullInsertion() = default;

	void _constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		ConvexHull<TSPType, Size, Caching, Partitioning>::runSingle(data);

		const size_t additions = Size - data.getRouteSize();
		for (size_t i = 0; i < additions; i++) {
			auto [closest_point, route_position] = ShortestInsertion<TSPType, Size, Caching, Partitioning>::FindClosestPoint(data);
			data.setCityPos(closest_point, route_position + 1);
		}
	};
};