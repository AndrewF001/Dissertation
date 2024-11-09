#pragma once
#include "construction_base.h"
#include "convex_hull.h"
#include "../tsp_data/tsp_data_template.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class LookaheadConvexHull : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	LookaheadConvexHull(const size_t depth) : ConstructionBase<TSPType, Size, Caching, Partitioning>(), m_depth(depth) {
#ifdef _DEBUG
		if (depth == 0)
			throw std::invalid_argument("Depth must be greater than 0");
#endif
	};
	~LookaheadConvexHull() = default;

	void constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		ConvexHull<TSPType, Size, Caching, Partitioning>::runSingle(data);

		const size_t additions = Size - data.getRouteSize();
		for (size_t i = 0; i < additions; i++) {
			auto [closest_point, route_position] = FindClosestPoints(data);
			data.setCityPos(closest_point, route_position);
		}

		std::cout << "Lookahead Convex Hull\n";
	};

private:
	const size_t m_depth;

	std::pair<cityID, cityID> FindClosestPoints(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) {
		std::pair<cityID, cityID> output;
		double min_dist = DBL_MAX;
		size_t depth = m_depth;

		if (Size - data.getRouteSize() < m_depth)
			depth = Size - data.getRouteSize();

		for (cityID idx = 0; idx < Size; idx++) {
			if (data.isCityInRoute(idx)) continue;

			auto [distance, position] = ShortestRoute(data, idx, depth, min_dist);
			if (distance < min_dist) {
				min_dist = distance;
				output = { idx, position };
			}
		}
		return output;
	}

	std::pair<double, cityID> ShortestRoute(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data, cityID point, size_t depth, const double best_distance) {
		std::pair<double, cityID> output = { DBL_MAX, SIZE_MAX };
		std::vector<cityID> partail_route;
		partail_route.reserve(depth + 2);
		partail_route.resize(3);
		partail_route[1] = point;
		

		const auto& route = data.getRoute();
		// find closest point to point
		for (size_t i = 0; i < data.getRouteSize(); i++) {
			double distance = data.calcDeivation(partail_route[1], data.getRouteCityID(route[i]), data.getRouteCityID(route[i + 1]));
			if (distance < output.first) {
				output.first = distance;
				output.second = i;
			}
		}

		// Add it to partail route
		partail_route[0] = data.getRouteCityID(route[output.second]);
		partail_route[2] = data.getRouteCityID(route[output.second + 1]);

		// Repeat for lookaheads
		// Find closest point that is apart of partail route
		for (size_t i = 0; i < depth - 1; i++) {
			double min_dist = DBL_MAX;
			std::pair<cityID, size_t> add_point = { SIZE_MAX, SIZE_MAX };

			for (cityID k = 0; k < Size; k++) {
				if (data.isCityInRoute(k)) 
					continue;

				// Check if point is already in partail route
                if (std::any_of(partail_route.begin() + 1, partail_route.end() - 1, [k](const auto& route_point) { return route_point == k; })) continue;

				for (size_t j = 0; j < partail_route.size() - 1; j++) {
					double distance = data.calcDeivation(k, partail_route[j], partail_route[j + 1]);
					if (distance < min_dist) {
						min_dist = distance;
						add_point = { k, j };
					}
				}
			}

			// add closest point to partail route
			partail_route.insert(partail_route.begin() + add_point.second + 1, add_point.first);
			output.first += min_dist;

			if (output.first > best_distance)	// TODO: Optimisation doesn't work as intended
				break;
		}
		
		return output;
	}
};