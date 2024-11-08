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
			//data.setCityPos(closest_point, route_position);
		}

		std::cout << "Lookahead Convex Hull\n";
	};

private:
	const size_t m_depth;

	std::pair<size_t, size_t> FindClosestPoints(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) {
		std::pair<size_t, size_t> output;
		double min_dist = DBL_MAX;
		size_t depth = 0;

		if (Size + 1 - data.getRouteSize() < m_depth)
			depth = Size + 1 - data.getRouteSize();

		for (cityID i = 0; i < Size; i++) {
			if (data.isCityInRoute(i)) continue;

			auto [distance, index] = ShortestRoute(data, i, depth, min_dist);
			if (distance < min_dist) {
				min_dist = distance;
				output = { i, index };
			}
		}

		return output;
	}

	std::pair<double, cityID> ShortestRoute(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data, cityID point, size_t depth, const double best_distance) {
		std::pair<double, cityID> output = { DBL_MAX, 0 };
		/*
		std::vector<TSPType&> partail_route;
		partail_route.reserve(m_depth + 1);
		partail_route.push_back(point);
		auto& cities = data.getAllCities();
		auto& route = data.getRoute();
		// find closest point to point
		for (size_t i = 0; i < data.getRouteSize()-1; i++) {
			double distance = point.getDistance(route[i], route[i + 1]) - route[i].getDistane(route[i+1]);
			if (distance < output.first) {
				output.first = distance;
				output.second = i;
			}
		}
		/*
		// Add it to partail route
		partail_route.insert(partail_route.begin(), data.route[output.second]);
		partail_route.push_back(data.route[output.second + 1]);

		// Set visited to true so that it isn't added again
		partail_route[1]->visited = true;

		// Repeat for lookaheads
		// Find closest point that is apart of partail route
		for (size_t i = 0; i < depth - 1; i++) {
			double min_dist = DBL_MAX;
			std::pair<Point*, size_t> add_point = { nullptr, 0 };

			for (size_t j = 0; j < partail_route.size() - 1; j++) {
				for (size_t k = 0; k < data.size; k++) {
					if (data.cities[k].visited) continue;

					double distance = partail_route[j]->square_distance(data.cities[k]) + partail_route[j + 1]->square_distance(data.cities[k]) - partail_route[j]->square_distance(*partail_route[j + 1]);
					if (distance < min_dist) {
						min_dist = distance;
						add_point = { &data.cities[k], j };
					}
				}
			}

			// add closest point to partail route
			partail_route.insert(partail_route.begin() + add_point.second + 1, add_point.first);
			add_point.first->visited = true;
			output.first += min_dist;

			if (output.first > best_distance)
				break;
		}

		// Set partail route to unvisited as they haven't been added to the route yet
		for (size_t i = 1; i < partail_route.size() - 1; i++) {
			partail_route[i]->visited = false;
		}
		//*/
		return output;
	}
};