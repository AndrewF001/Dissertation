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
	TspTemplate(const Square& size) : m_data(size) {};	// !!! ONLY USE FOR DEBUGGING !!!
	TspTemplate(const Square& size, GenerationType type, std::mt19937& seed) : m_data(size, type, seed) {};
	TspTemplate(const Square& size, std::array<TSPType, Size> cities) : m_data(size, cities) {};

	~TspTemplate() = default;

	void run() {
		m_data.initalisePartition();
		m_data.initaliseCache();
		ConstructTour();
		OptimiseTour();
	};

public:	// TODO: Change to private later
	// Implement both
	std::array<size_t, Size> m_tour{};	// TODO: look into index assignment (city[i] = pos) vs value assignment (arr[i] = city)
	TspDataTemplate<TSPType, Size, Caching, Partitioning> m_data;

	void ConstructTour() {
		if constexpr (Optimisation == OptimisationType::kopt)
			Kopt<TSPType, Size, Caching, Partitioning>(m_data).optimiseTour();	// Virtual method can't be static
	};

	void OptimiseTour() {
		if constexpr (Construction == ContructionType::LookaheadConvexHull)
			LookaheadConvexHull<TSPType, Size, Caching, Partitioning>(m_data).constructTour();	// Virtual method can't be static
	};
};
