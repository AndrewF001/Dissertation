#pragma once
#include <vector>
#include <chrono>
#include <random>

#include "tsp_data/tsp_constructs.h"
#include "tour_optimisation/optimisation_headers.h"
#include "tour_construction/consturction_headers.h"
#include "timer.h"

// Not enough info to reproduce results but sames timing results
class TSPResult {
public:
	// Contruction parameters
	Square area;
	std::mt19937 seed;
	GenerationType genType;
	size_t num_cities;	// Number of cities

	// Completed route
	double constructTour_distance;
	double final_distance;

	// Run settings
	CachingType Caching;
	PartitioningType Partitioning;
	ConstructionType Construction;
	OptimisationType Optimisation;

	// Run statistics
	bool validRoute;
	TimeScale total_run_time;
	TimeScale initalisePartition_time;
	TimeScale initaliseCache_time;
	TimeScale constructTour_time;
	TimeScale optimiseTour_time;

	std::string csvLine() {
		std::string output = "";


	}

};

// Fully reconstructable results
class TSPVerboseResult : public TSPResult {
public:
	// .tsp file data fields
	std::string name;	// File name
	std::string type;	// Type of TSP
	std::string comment;
	std::string edge_weight_type;	// Type of data used for edge weights
	std::string display_data_type;
	std::vector<Point2D> node_coord_section;

	std::vector<cityID> route;

	std::string csvLine() {
		std::string output = TSPResult::csvLine();

		return output;
	}
};