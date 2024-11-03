#pragma once
#include "tsp_data/tsp_data_template.h"
#include "tsp_data/types/type_base.h"
#include "tsp_data/types/2d.h"
//#include "tsp_data/types/2d.cpp"
#include "tour_construction/lookahead_convex_hull.h"
#include "tour_optimisation/k_opt.h"


template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning, ContructionType Construction, OptimisationType Optimisation>
class TspTemplate {

public:
	TspTemplate(const Cube& size) : m_data(size) {};
	~TspTemplate() = default;

	void run() {
		m_data.initalisePartition();
		m_data.initaliseCache();
		ConstructTour();
		//m_construction.constructTour();
		OptimiseTour();
		//m_optimisation.optimiseTour();
	};

public:	// TODO: Change to private later
	TspDataTemplate<TSPType, Size, Caching, Partitioning> m_data;
	//Construction m_construction;
	//Optimisation m_optimisation;

	void ConstructTour() {
		if (Optimisation == OptimisationType::kopt)	// constexpr
			Kopt<TSPType, Size, Caching, Partitioning>(m_data).optimiseTour();	// Virtual method can't be static
	};

	void OptimiseTour() {
		if (Construction == ContructionType::LookaheadConvexHull) // constexpr
			LookaheadConvexHull<TSPType, Size, Caching, Partitioning>(m_data).constructTour();	// Virtual method can't be static
	};
};
