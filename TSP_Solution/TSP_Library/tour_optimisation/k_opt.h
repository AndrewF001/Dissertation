#pragma once
#include "optimisation_base.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class KOpt : public OptimisationBase<TSPType, Size, Caching, Partitioning> {
public:
	KOpt() : OptimisationBase<TSPType, Size, Caching, Partitioning>() {};
	~KOpt() = default;

	void optimiseTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) override {
		std::cout << "Kopt\n";
	};
};