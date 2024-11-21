#pragma once
#include "../tsp_data/tsp_data_template.h"

enum class OptimisationType {
	None,
	Kopt,
	TwoOpt,
};

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class OptimisationBase {
public:
	OptimisationBase() = default;
	virtual ~OptimisationBase() = default;

	virtual void optimiseTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) = 0;

//protected:
//	TspDataTemplate<TSPType, Size, Caching, Partitioning>& m_data_ref;
};