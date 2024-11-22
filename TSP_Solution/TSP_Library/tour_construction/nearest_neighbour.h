#pragma once
#include "construction_base.h"
#include "../tsp_data/tsp_data_template.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class NearestNeighbour : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	NearestNeighbour() : ConstructionBase<TSPType, Size, Caching, Partitioning>() {};
	~NearestNeighbour() = default;

	void constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		std::cout << "Nearest Neighbour\n";

		data.setCityPos(0, 0);	// Randomly select the first city
		for (size_t i = 1; i < Size; i++) {
			auto [closest_point, route_position] = FindClosestPoint(data);
			data.setCityPos(closest_point, route_position + 1);
		}
	};

private:

	std::pair<cityID, size_t> FindClosestPoint(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) {
		double min_dist = DBL_MAX;
		std::pair<cityID, size_t> output;
		const auto& route = data.getRoute();

		for (cityID idx = 0; idx < data.getRouteSize(); idx++) {

			double offset = min_dist * min_dist;
			
			auto point = route[idx]->getPoint();
			std::vector<cityID> city_search = data.getCitiesInArea(Square({ point.x - offset, point.y - offset }, offset * 2, offset * 2));

			for (size_t i = 0; i < city_search.size(); i++) {
				if (data.isCityInRoute(city_search[i])) 
					continue;

				double distance = data.getDistance(city_search[i], data.getRouteCityID(route[idx]));
				if (distance < min_dist) {
					min_dist = distance;
					output = { city_search[i], idx };
				}
			}
		}

		return output;
	}
};