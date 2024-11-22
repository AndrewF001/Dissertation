#pragma once
#include "optimisation_base.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class ThreeOpt : public OptimisationBase<TSPType, Size, Caching, Partitioning> {
public:
    ThreeOpt() : OptimisationBase<TSPType, Size, Caching, Partitioning>() {};
    ~ThreeOpt() = default;

    void optimiseTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
        std::cout << "ThreeOpt\n";

        size_t n = data.getRouteSize();
        auto& route = data.getRoute();

        // Inspired by https://en.wikipedia.org/wiki/2-opt#C++_code
        bool found_improvement = true;
        while (found_improvement) {
            found_improvement = false;
            for (size_t i = 0; i < n - 4; i++) {
                for (size_t j = i + 2; j < n - 2; j++) {
                    for (size_t k = j + 2;  k < n;  k++)
                    {
						double i_length = route[i]->getDistance(route[i + 1]);
						double j_length = route[j]->getDistance(route[j + 1]);
						double k_length = route[k]->getDistance(route[k + 1]);
						double orignal_length = -i_length - j_length - k_length;


                        double delta_length = 0;

                        if (delta_length < 0) { // If new edges are shorter, swap them
                            data.swapRoutePos(i, j);
                            found_improvement = true;
                        }
                    }
                }
            }
        }
    };
};