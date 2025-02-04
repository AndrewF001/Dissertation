#pragma once
#include "construction_base.h"
#include "convex_hull.h"
#include "../tsp_data/tsp_data_template.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class StaticLookahead : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	StaticLookahead(const size_t depth) : ConstructionBase<TSPType, Size, Caching, Partitioning>("StaticLookahead"), m_depth(depth) {
#ifdef _DEBUG
		if (depth == 0)
			throw std::invalid_argument("Depth must be greater than 0");
#endif
	};
	~StaticLookahead() = default;

	void _constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		data.setCityPos(0, 0);	// Randomly select the first city

		lookaheadInsertion(data, m_depth);
	};

	static void lookaheadInsertion(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data, size_t depth) {
		const size_t additions = Size - data.getRouteSize();
		for (size_t i = 0; i < additions; i++) {
			auto [closest_point, route_position] = FindClosestPoints(data, depth);
			data.setCityPos(closest_point, route_position + 1);
		}
	}

	static std::pair<cityID, size_t> FindClosestPoints(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data, size_t depth) {
		double min_dist = DBL_MAX;
		std::pair<cityID, size_t> output;

		if (Size - data.getRouteSize() < depth)
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

private:
	const size_t m_depth;



	static std::pair<double, cityID> ShortestRoute(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data, cityID point, size_t depth, const double best_distance) {
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
		double offset = best_distance * best_distance;
		std::vector<cityID> city_search = data.getCitiesInArea(partail_route[1], offset);

		for (size_t i = 0; i < depth - 1; i++) {
			double min_dist = DBL_MAX;
			std::pair<cityID, size_t> add_point = { SIZE_MAX, SIZE_MAX };

			for (const auto& city : city_search) {	// TODO: use partitioning to reduce search space
				if (data.isCityInRoute(city))
					continue;

				// Check if point is already in partail route TODO: Optimize with isCityInRoute()
				if (std::any_of(partail_route.begin() + 1, partail_route.end() - 1, [city](const auto& route_point) { return route_point == city; }))
					continue;

				for (size_t j = 0; j < partail_route.size() - 1; j++) {
					double distance = data.calcDeivation(city, partail_route[j], partail_route[j + 1]);
					if (distance < min_dist) {
						min_dist = distance;
						add_point = { city, j };
					}
				}
			}

			if (add_point.first == SIZE_MAX)	// No point found
				break;

			// add closest point to partail route
			partail_route.insert(partail_route.begin() + add_point.second + 1, add_point.first);
			output.first += min_dist;

			if (output.first > best_distance)
				break;
		}

		return output;
	}
};