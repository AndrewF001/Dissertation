#pragma once
#include "tsp_data/tsp_data_template.h"
#include "tsp_data/types/type_base.h"
#include "tsp_data/types/2d.h"
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

	const TspDataTemplate<TSPType, Size, Caching, Partitioning>& getData() { return m_data; };
	const std::array<size_t, Size>& getTour() { return m_data.getRoute(); };

private:	// TODO: Change to private later
	TspDataTemplate<TSPType, Size, Caching, Partitioning> m_data;

	void ConstructTour() {
		if constexpr (Optimisation == OptimisationType::kopt)
			Kopt<TSPType, Size, Caching, Partitioning>(m_data).optimiseTour();	// Virtual method can't be static
	};

	void OptimiseTour() {
		if constexpr (Construction == ContructionType::LookaheadConvexHull)
			LookaheadConvexHull<TSPType, Size, Caching, Partitioning>().constructTour(m_data);	// Virtual method can't be static
	};
};
