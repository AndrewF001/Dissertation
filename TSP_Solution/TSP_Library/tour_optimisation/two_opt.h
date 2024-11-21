#pragma once
#include "optimisation_base.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class TwoOpt : public OptimisationBase<TSPType, Size, Caching, Partitioning> {
public:
	TwoOpt() : OptimisationBase<TSPType, Size, Caching, Partitioning>() {};
	~TwoOpt() = default;

	void optimiseTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		std::cout << "TwoOpt\n";

        size_t n = data.getRouteSize() - 1;
		auto& route = data.getRoute();

        // Inspired by https://en.wikipedia.org/wiki/2-opt#C++_code
        bool found_improvement = true;
        while (found_improvement) {
            found_improvement = false;
            for (size_t i = 0; i < n - 1; i++) {
                for (size_t j = i + 2; j < n; j++) {
                    double delta_length = (-route[i]->getDistance(route[i + 1]) - route[j]->getDistance(route[j + 1])) +    // Cost of the original edges
						(route[i]->getDistance(route[j]) + route[i + 1]->getDistance(route[j + 1]));                        // Cost of the new edges

					if (delta_length < 0) { // If new edges are shorter, swap them
                        data.swapRoutePos(i, j);
                        found_improvement = true;
                    }
                }
            }
        }
	};
};