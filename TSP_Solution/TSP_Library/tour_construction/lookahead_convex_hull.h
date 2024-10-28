#pragma once
#include "construction_base.h"

template<class TSPType, CachingType Caching, class Partitioning, size_t Size>
class LookaheadConvexHull : public ConstructionBase<TSPType, Caching, Partitioning, Size> {
public:
	LookaheadConvexHull(TspDataTemplate<TSPType, Caching, Partitioning, Size>& ref) : ConstructionBase<TSPType, Caching, Partitioning, Size>(ref) {};
	~LookaheadConvexHull() = default;

	void constructTour() {
		std::cout << "Lookahead Convex Hull\n";
		std::cout << this->m_data_ref.getAllCities()[0].m_point << "\n";
	};
};