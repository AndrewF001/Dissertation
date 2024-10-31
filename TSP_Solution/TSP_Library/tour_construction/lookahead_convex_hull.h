#pragma once
#include "construction_base.h"

template<class TSPType, size_t Size, CachingTypes Caching, class Partitioning>
class LookaheadConvexHull : public ConstructionBase<TSPType, Size, Caching, Partitioning> {
public:
	LookaheadConvexHull(TspDataTemplate<TSPType, Size, Caching, Partitioning>& ref) : ConstructionBase<TSPType, Size, Caching, Partitioning>(ref) {};
	~LookaheadConvexHull() = default;

	void constructTour() override {
		std::cout << "Lookahead Convex Hull\n";
		std::cout << this->m_data_ref.getAllCities()[0].m_point << "\n";
	};
};