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

		const size_t additions = Size - data.getRouteSize() + 1;
		for (size_t i = 0; i < additions; i++) {
			auto [closest_point, route_position] = FindClosestPoints(data);
			data.setCityPos(closest_point, route_position);
		}

		std::cout << "Lookahead Convex Hull\n";
	};

private:
	const size_t m_depth;

	std::pair<double, size_t> ShortestRoute(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data, TSPType& point, const double best_distance) {
		std::pair<double, size_t> output = { DBL_MAX, 0 };
		/*
		std::vector<size_t> partail_route = { point };

		// find closest point to point
		for (size_t i = 0; i < Size - 1; i++) {
			double distance = point->square_distance(*data.route[i], *data.route[i + 1]) - data.route[i]->square_distance(*data.route[i + 1]);
			if (distance < output.first) {
				output.first = distance;
				output.second = i;
			}
		}

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

	std::pair<size_t, size_t> FindClosestPoints(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) {
		std::pair<size_t, size_t> output;
		/*double min_dist = DBL_MAX;

		if (data.size + 1 - data.route.size() < depth)
			depth = data.size + 1 - data.route.size();

		for (size_t i = 0; i < data.size; i++) {
			if (data.cities[i].visited) continue;

			auto [distance, index] = ShortestRoute(data, &data.cities[i], depth, min_dist);
			if (distance < min_dist) {
				min_dist = distance;
				output = { &data.cities[i], index };
			}
		}

		*/ 
		return output;
	}
};