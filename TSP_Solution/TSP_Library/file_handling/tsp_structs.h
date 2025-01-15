#pragma once
#include <vector>
#include <chrono>
#include <random>
#include <omp.h>

#include "../tsp_data/tsp_constructs.h"
#include "../tour_optimisation/optimisation_headers.h"
#include "../tour_construction/consturction_headers.h"
#include "timer.h"

enum Validity {
	Valid,
	Invalid,
	Timeout
};

class TSPArgs {
public:
	size_t max_depth = 1;
	int num_threads = omp_get_max_threads();
	std::chrono::milliseconds timeout_ms = std::chrono::milliseconds(60000);
	
	friend auto operator==(const TSPArgs& lhs, const TSPArgs& rhs) {
		return lhs.max_depth == rhs.max_depth &&
			lhs.num_threads == rhs.num_threads;
	}
};

// TSP Run Settings
class RunMode {
public:
	size_t id = 0;

	size_t num_cities;
	GenerationType genType;

	CachingType Caching;
	PartitioningType Partitioning;
	ConstructionType Construction;
	OptimisationType Optimisation;

	TSPArgs args;

	void set(const RunMode& copy) {
		num_cities = copy.num_cities;
		genType = copy.genType;
		Caching = copy.Caching;
		Partitioning = copy.Partitioning;
		Construction = copy.Construction;
		Optimisation = copy.Optimisation;
		args = copy.args;
	}

	friend auto operator==(const RunMode& lhs, const RunMode& rhs) {
		return lhs.num_cities == rhs.num_cities &&
			lhs.genType == rhs.genType &&
			lhs.Caching == rhs.Caching &&
			lhs.Partitioning == rhs.Partitioning &&
			lhs.Construction == rhs.Construction &&
			lhs.Optimisation == rhs.Optimisation &&
			lhs.args == rhs.args;

	}
};

// Not enough info to reproduce results but saves timing results
class TSPResult : public RunMode {
public:
	// Additional Contruction Parameters
	Square area;
	unsigned int seed;

	// Completed route
	double constructTour_distance;
	double final_distance;

	// Run statistics
	Validity validRoute;
	TimeScale total_run_time{};
	TimeScale initalisePartition_time{};
	TimeScale initaliseCache_time{};
	TimeScale constructTour_time{};
	TimeScale optimiseTour_time{};
};

class TSPVerboseResultStatic : public TSPResult {
public:
	// .tsp file data fields
	std::string name;	// File name
	std::string type;	// Type of TSP
	std::string comment;
	std::string edge_weight_type;	// Type of data used for edge weights
	std::string display_data_type;
};

// Fully reconstructable results
class TSPVerboseResultDynamic : public TSPVerboseResultStatic {
public:
	std::vector<Point2D> node_coord_section;
	std::vector<cityID> route;
};

// Statistics for multiple runs
class StatisticEntry : public RunMode {
public:
	size_t number_of_runs;
	size_t number_of_valid_routes;
	size_t invalidRoutes;
	size_t timeouts;

	double total_construct_tour_distance;
	double total_final_distance;

	TimeScale total_run_time;
	TimeScale total_initalisePartition_time;
	TimeScale total_initaliseCache_time;
	TimeScale total_constructTour_time;
	TimeScale total_optimiseTour_time;

	void append(const TSPVerboseResultDynamic& data) {
		number_of_runs++;

		switch (data.validRoute) {
		case (Valid):
			number_of_valid_routes++;
			break;
		case (Invalid):
			invalidRoutes++;
			return;
		case (Timeout):
			timeouts++;
			return;
		}

		total_construct_tour_distance += data.constructTour_distance;
		total_final_distance += data.final_distance;

		total_run_time += data.total_run_time;
		total_initaliseCache_time += data.initaliseCache_time;
		total_initalisePartition_time += data.initalisePartition_time;
		total_constructTour_time += data.constructTour_time;
		total_optimiseTour_time += data.optimiseTour_time;
	}
};
