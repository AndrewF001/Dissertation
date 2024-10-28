#pragma once
#include "../tsp_data/data/tsp_data_template.h"

enum class OptimisationType {
	kopt,
	LinKernighan
};

template<class TSPType, CachingType Caching, class Partitioning, size_t Size>
class OptimisationBase {
public:
	OptimisationBase(TspDataTemplate<TSPType, Caching, Partitioning, Size>& ref) : m_data_ref(ref) {};
	~OptimisationBase() = default;

	virtual void optimiseTour() = 0;

protected:
	TspDataTemplate<TSPType, Caching, Partitioning, Size>& m_data_ref;
};