#pragma once
#include "tsp_data/data/tsp_data_template.h"
#include "tsp_data/data/types/type_base.h"
#include "tsp_data/data/types/2d.h"
#include "tsp_data/data/types/2d.cpp"
#include "tour_construction/lookahead_convex_hull.h"
#include "tour_optimisation/k_opt.h"

template <class TSPType, CachingType Caching, class Partitioning, size_t Size, class Construction, class Optimisation>
class TspTemplate {

public:
	TspTemplate(const Cube& size) : m_data(size), m_construction(m_data), m_optimisation(m_data) {};
	~TspTemplate() = default;

	void run() {
		m_data.initaliseCache();
		m_construction.constructTour();
		m_optimisation.optimiseTour();
	};

public:	// TODO: Change to private later
	TspDataTemplate<TSPType, Caching, Partitioning, Size> m_data;
	Construction m_construction;
	Optimisation m_optimisation;
};
