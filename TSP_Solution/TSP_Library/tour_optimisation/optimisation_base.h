#pragma once
#include "../tsp_data/tsp_data_template.h"

enum class OptimisationType {
	None,
	kopt,
	LinKernighan
};

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class OptimisationBase {
public:
	OptimisationBase(TspDataTemplate<TSPType, Size, Caching, Partitioning>& ref) : m_data_ref(ref) {};
	virtual ~OptimisationBase() = default;

	virtual void optimiseTour() = 0;

protected:
	TspDataTemplate<TSPType, Size, Caching, Partitioning>& m_data_ref;
};