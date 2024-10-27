#pragma once
#include "optimisation_base.h"

template<class TSPType, CachingType Caching, class Partitioning>
class Kopt : public OptimisationBase<TSPType, Caching, Partitioning> {
public:
	Kopt(TspDataTemplate<TSPType, Caching, Partitioning>& ref) : OptimisationBase<TSPType, Caching, Partitioning>(ref) {};
	~Kopt() = default;

	void optimiseTour() {
		std::cout << "Kopt\n";
		std::cout << this->m_data_ref.getAllCities()[1].m_point << "\n";
	};
};