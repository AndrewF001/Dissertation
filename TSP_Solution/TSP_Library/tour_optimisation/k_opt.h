#pragma once
#include "optimisation_base.h"

template<class TSPType, size_t Size, CachingTypes Caching, class Partitioning>
class Kopt : public OptimisationBase<TSPType, Size, Caching, Partitioning> {
public:
	Kopt(TspDataTemplate<TSPType, Size, Caching, Partitioning>& ref) : OptimisationBase<TSPType, Size, Caching, Partitioning>(ref) {};
	~Kopt() = default;

	void optimiseTour() override {
		std::cout << "Kopt\n";
		std::cout << this->m_data_ref.getAllCities()[1].m_point << "\n";
	};
};