#pragma once
#include "construction_base.h"
#include "convex_hull.h"
#include "../tsp_data/tsp_data_template.h"

struct DynamicArgs {	// These numbers are from a Gradient descent analysis
	double multiplier = 1.2348586676954691;
	double logrithm = 0.90649189814814557;
	double constant = -1.6065204475308614;

	friend auto operator==(const DynamicArgs& lhs, const DynamicArgs& rhs) {
		return lhs.multiplier == rhs.multiplier &&
			lhs.logrithm == rhs.logrithm &&
			lhs.constant == rhs.constant;
	}
};

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class DynamicLookahead : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	DynamicLookahead(const size_t depth, const DynamicArgs args) : ConstructionBase<TSPType, Size, Caching, Partitioning>("DynamicLookahead"), m_max_depth(depth), m_args(args) {
#ifdef _DEBUG
		if (depth == 0)
			throw std::invalid_argument("Depth must be greater than 0");
#endif
	};
	~DynamicLookahead() = default;

	void _constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		data.setCityPos(0, 0);	// Randomly select the first city

		dynamicLookaheadInsertion(data, m_max_depth, m_args);
	};

	static size_t optimalDepth(size_t size, size_t max_depth, DynamicArgs& args) {
		size_t optimal = (size_t)std::round(args.multiplier * std::log(args.logrithm * size) - args.constant);

		if (optimal == 0)
			optimal = 1;
		
		return std::min(optimal, max_depth);
	}

	static void dynamicLookaheadInsertion(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data, size_t max_depth, DynamicArgs args) {
		const size_t additions = Size - data.getRouteSize();
		size_t depth = optimalDepth(additions, max_depth, args);
		for (size_t i = additions; i > 0; i--) {
			auto [closest_point, route_position] = StaticLookahead<TSPType, Size, Caching, Partitioning>::FindClosestPoints(data, depth);
			data.setCityPos(closest_point, route_position + 1);
		}
	}

private:
	const size_t m_max_depth;
	const DynamicArgs m_args;
};