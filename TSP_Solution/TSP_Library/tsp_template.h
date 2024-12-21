#pragma once
#include <omp.h>
#include <future>
#include <chrono>
#include <thread>

#include "timer.h"
#include "logger.h"

#include "tsp_output.h"
#include "tsp_data/types_headers.h"
#include "tour_construction/consturction_headers.h"
#include "tour_optimisation/optimisation_headers.h"



template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning, ConstructionType Construction, OptimisationType Optimisation>
class TspTemplate {

public:
	TspTemplate(const Square& size) : m_data(size) {};	// !!! ONLY USE FOR DEBUGGING !!!
	TspTemplate(const Square& size, GenerationType type, std::mt19937& seed) : m_data(size, type, seed) {
		m_output.seed = seed;
		m_output.genType = type;
	};
	TspTemplate(const Square& size, std::array<TSPType, Size> cities) : m_data(size, cities) {};
	~TspTemplate() = default;

	TSPVerboseResult run(size_t depth = 1, int max_threads = omp_get_max_threads()) {
		// package task to cancel if it takes too long
		std::packaged_task<void()> task(std::bind(&TspTemplate::_run, this, depth, max_threads));

		// Future for probing status
		auto future = task.get_future();

		// Start the task in a separate thread
		std::thread thr(std::move(task));

		// Wait for the task to finish or timeout
		if (future.wait_for(std::chrono::seconds(10)) != std::future_status::timeout) {
			// Task was succefully completed
			thr.join();
			future.get();
		} else {
			// Task took too long
			thr.detach();
			Logger::error("Timeout");

			m_output.validRoute = false;
			m_output.total_run_time = TimeScale::max();
		}

		return m_output;
	}

	const TspDataTemplate<TSPType, Size, Caching, Partitioning>& getData() const { return m_data; };
	const std::array<TSPType*, Size + 1>& getRoute() const { return m_data.getRoute(); };
	bool validRoute() const { return m_data.validRoute(); };
	const TSPVerboseResult& getOutput() const { return m_output; }

	void finaliseOutput() { 
		for (const auto& r : m_data.getRoute()) {
			m_output.route.push_back(m_data.getRouteCityID(r));
		}

		for (size_t i = 0; i < Size; i++) {
			m_output.node_coord_section.push_back(m_data.getCityPoint(i));
		}

		m_output.area = m_data.m_area;
		m_output.validRoute = validRoute();
		m_output.Caching = Caching;
		m_output.Partitioning = Partitioning;
		m_output.Construction = Construction;
		m_output.num_cities = Size;
	};

private:
	TspDataTemplate<TSPType, Size, Caching, Partitioning> m_data;
	TSPVerboseResult m_output;
	Timer m_timer;

	void _run(size_t depth = 1, int max_threads = omp_get_max_threads()) {
		if (m_data.getNumberOfCities() != Size)
			throw std::invalid_argument("Number of cities does not match the size of the template! Fill all data entries");

		omp_set_num_threads(max_threads);
		m_timer.start_timer();

		m_data.initalisePartition();
		m_output.initalisePartition_time = m_timer.interval();

		m_data.initaliseCache();
		m_output.initaliseCache_time = m_timer.interval();

		constructTour(depth, max_threads);
		m_output.constructTour_time = m_timer.interval();
		double distance = m_data.getRouteLength();
		Logger::log("Original Route Length: " + std::to_string(distance) + "\n", 2);
		m_output.constructTour_distance = distance;
		m_timer.start_timer();


		optimiseTour(max_threads);
		m_output.optimiseTour_time = m_timer.interval();
		m_output.total_run_time = m_timer.stopTimer();
		distance = m_data.getRouteLength();
		Logger::log("Improved Route Length: " + std::to_string(distance) + "\n", 2);
		m_output.final_distance = distance;

		finaliseOutput();
	};

	void constructTour(size_t depth, size_t max_threads) {
		if constexpr (Construction == ConstructionType::StaticLookaheadConvexHullInserstion)
			StaticLookaheadConvexHull<TSPType, Size, Caching, Partitioning>(depth).constructTour(m_data);

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
