#pragma once
#include <omp.h>

#include "tsp_output.h"
#include "tsp_data/types_headers.h"
#include "tour_construction/consturction_headers.h"
#include "tour_optimisation/optimisation_headers.h"

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning, ConstructionType Construction, OptimisationType Optimisation>
class TspTemplate {

public:
	TspTemplate(const Square& size) : m_data(size) {};	// !!! ONLY USE FOR DEBUGGING !!!
	TspTemplate(const Square& size, GenerationType type, std::mt19937& seed) : m_data(size, type, seed) {};
	TspTemplate(const Square& size, std::array<TSPType, Size> cities) : m_data(size, cities) {};
	~TspTemplate() = default;

	void run(size_t depth = 1, int max_threads = omp_get_max_threads()) {
		if (m_data.getNumberOfCities() != Size)
			throw std::invalid_argument("Number of cities does not match the size of the template! Fill all data entries");

		omp_set_num_threads(max_threads);

		m_data.initalisePartition();
		m_data.initaliseCache();

		constructTour(depth, max_threads);
		std::cout << "Original Route Length: " << m_data.getRouteLength() << std::endl;
		
		optimiseTour(max_threads);
		std::cout << "Improved Route Length: " << m_data.getRouteLength() << std::endl;
	};

	const TspDataTemplate<TSPType, Size, Caching, Partitioning>& getData() const { return m_data; };
	const std::array<TSPType*, Size + 1>& getRoute() const { return m_data.getRoute(); };
	bool validRoute() const { return m_data.validRoute(); };
	TSPOutput getOutput() const { 
		TSPOutput output;
		auto r = m_data.getRoute();
		for (size_t i = 0; i < Size + 1; i++) {
			output.route.push_back(m_data.getRouteCityID(r[i]));
		}

		for (size_t i = 0; i < Size; i++) {
			output.node_coord_section.push_back(m_data.getCityPoint(i));
		}
		output.area = m_data.m_area;
		return output;
	};

private:
	TspDataTemplate<TSPType, Size, Caching, Partitioning> m_data;

	void constructTour(size_t depth, size_t max_threads) {
		if constexpr (Construction == ConstructionType::LookaheadConvexHull)
			LookaheadConvexHull<TSPType, Size, Caching, Partitioning>(depth).constructTour(m_data);

		if constexpr (Construction == ConstructionType::NearestNeighbour)
			NearestNeighbour<TSPType, Size, Caching, Partitioning>().constructTour(m_data);

		if constexpr (Construction == ConstructionType::ShortestInsertion)
			ShortestInsertion<TSPType, Size, Caching, Partitioning>().constructTour(m_data);

		if constexpr (Construction == ConstructionType::ConvexHullInsertion)
			ConvexHullInsertion<TSPType, Size, Caching, Partitioning>().constructTour(m_data);
			
	};

	void optimiseTour(size_t max_threads) {
		if constexpr (Optimisation == OptimisationType::TwoOpt)
			TwoOpt<TSPType, Size, Caching, Partitioning>().optimiseTour(m_data);
		
		//if constexpr (Optimisation == OptimisationType::ThreeOpt)
			//ThreeOpt<TSPType, Size, Caching, Partitioning>().optimiseTour(m_data);

		//if constexpr (Optimisation == OptimisationType::Kopt)
			//KOpt<TSPType, Size, Caching, Partitioning>().optimiseTour(m_data);
	};
};
