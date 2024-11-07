#pragma once
#include <omp.h>
#include "tsp_data/tsp_data_template.h"
#include "tsp_data/types/type_base.h"
#include "tsp_data/types/2d.h"
#include "tour_construction/lookahead_convex_hull.h"
#include "tour_optimisation/k_opt.h"

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning, ConstructionType Construction, OptimisationType Optimisation>
class TspTemplate {

public:
	TspTemplate(const Square& size) : m_data(size) {};	// !!! ONLY USE FOR DEBUGGING !!!
	TspTemplate(const Square& size, GenerationType type, std::mt19937& seed) : m_data(size, type, seed) {};
	TspTemplate(const Square& size, std::array<TSPType, Size> cities) : m_data(size, cities) {};
	~TspTemplate() = default;

	void run(size_t depth = 1, size_t max_threads = omp_get_max_threads()) {
		if (m_data.getNumberOfCities() != Size)
			throw std::invalid_argument("Number of cities does not match the size of the template! Fill all data entries");

		omp_set_num_threads(max_threads);

		m_data.initalisePartition();
		m_data.initaliseCache();
		constructTour(depth, max_threads);
		optimiseTour(max_threads);
	};

	const TspDataTemplate<TSPType, Size, Caching, Partitioning>& getData() const { return m_data; };
	const std::array<size_t, Size>& getRoute() const { return m_data.getRoute(); };

private:
	TspDataTemplate<TSPType, Size, Caching, Partitioning> m_data;

	void constructTour(size_t depth, size_t max_threads) {
		if constexpr (Construction == ConstructionType::LookaheadConvexHull)
			LookaheadConvexHull<TSPType, Size, Caching, Partitioning>(depth).constructTour(m_data);	// Virtual method can't be static
	};

	void optimiseTour(size_t max_threads) {
		if constexpr (Optimisation == OptimisationType::kopt)
			Kopt<TSPType, Size, Caching, Partitioning>(m_data).optimiseTour();	// Virtual method can't be static
	};
};
