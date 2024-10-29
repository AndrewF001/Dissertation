#pragma once
#include "../tsp_data/data/tsp_data_template.h"

enum class OptimisationType {
	kopt,
	LinKernighan
};

template<class TSPType, size_t Size, CachingTypes Caching, class Partitioning>
class OptimisationBase {
public:
	OptimisationBase(TspDataTemplate<TSPType, Size, Caching, Partitioning>& ref) : m_data_ref(ref) {};
	~OptimisationBase() = default;

	virtual void optimiseTour() = 0;

protected:
	TspDataTemplate<TSPType, Size, Caching, Partitioning>& m_data_ref;
};