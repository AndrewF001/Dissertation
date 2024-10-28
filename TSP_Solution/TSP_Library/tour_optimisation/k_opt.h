#pragma once
#include "optimisation_base.h"

template<class TSPType, CachingType Caching, class Partitioning, size_t Size>
class Kopt : public OptimisationBase<TSPType, Caching, Partitioning, Size> {
public:
	Kopt(TspDataTemplate<TSPType, Caching, Partitioning, Size>& ref) : OptimisationBase<TSPType, Caching, Partitioning, Size>(ref) {};
	~Kopt() = default;

	void optimiseTour() {
		std::cout << "Kopt\n";
		std::cout << this->m_data_ref.getAllCities()[1].m_point << "\n";
	};
};