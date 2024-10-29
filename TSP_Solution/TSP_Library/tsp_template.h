#pragma once
#include "tsp_data/tsp_data_template.h"
#include "tsp_data/types/type_base.h"
#include "tsp_data/types/2d.h"
#include "tsp_data/types/2d.cpp"
#include "tsp_data/partitioning/no_partitioning.h"
#include "tour_construction/lookahead_convex_hull.h"
#include "tour_optimisation/k_opt.h"


template <class TSPType, size_t Size, CachingTypes Caching, class Partitioning, class Construction, class Optimisation>
class TspTemplate {

public:
	TspTemplate(const Cube& size) : m_data(size), m_construction(m_data), m_optimisation(m_data) {};
	~TspTemplate() = default;

	void run() {
		m_data.initalisePartition();
		m_data.initaliseCache();
		m_construction.constructTour();
		m_optimisation.optimiseTour();
	};

public:	// TODO: Change to private later
	TspDataTemplate<TSPType, Size, Caching, Partitioning> m_data;
	Construction m_construction;
	Optimisation m_optimisation;
};
