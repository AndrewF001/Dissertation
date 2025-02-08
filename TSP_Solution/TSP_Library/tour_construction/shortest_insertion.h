#pragma once
#include "construction_base.h"
#include "../tsp_data/tsp_data_template.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class ShortestInsertion : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	ShortestInsertion() : ConstructionBase<TSPType, Size, Caching, Partitioning>("ShortestInsertion") {};
	~ShortestInsertion() = default;

	void _constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		data.setCityPos(0, 0);	// Randomly select the first city

		for (size_t i = 1; i < Size; i++) {
			auto [closest_point, route_position] = FindClosestPoint(data);
			data.setCityPos(closest_point, route_position + 1);
		}
	};

	static std::pair<cityID, size_t> FindClosestPoint(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) {
		double min_dist = DBL_MAX;
		std::pair<cityID, size_t> output;
		const auto& route = data.getRoute();

		for (cityID idx = 0; idx < data.getRouteSize(); idx++) {
			double offset = min_dist * min_dist;
			std::vector<cityID> city_search = data.getCitiesInArea(idx, offset);

			for (size_t i = 0; i < city_search.size(); i++) {
				if (data.isCityInRoute(city_search[i]))
					continue;

				double distance = data.calcDeivation(city_search[i], data.getRouteCityID(route[idx]), data.getRouteCityID(route[idx + 1]));
				if (distance < min_dist) {
					min_dist = distance;
					output = { city_search[i], idx };
				}
			}
		}

		return output;
	}
};