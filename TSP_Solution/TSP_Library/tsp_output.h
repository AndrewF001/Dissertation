#pragma once
#include <vector>
#include <chrono>
#include <random>

#include "tsp_data/tsp_constructs.h"

struct TSPOutput {
	// .tsp file data fields
	std::string name;	// File name
	std::string type;	// Type of TSP
	std::string comment;
	size_t dimension;	// Number of cities
	std::string edge_weight_type;	// Type of data used for edge weights
	std::string display_data_type;
	std::vector<Point2D> node_coord_section;

	// Contruction par
	Square area;
	std::mt19937 seed;

	// Completed route
	double distance;
	std::vector<cityID> route;

	// Run statistics
	std::chrono::milliseconds run_time;
	std::chrono::milliseconds initalisePartition_time;
	std::chrono::milliseconds initaliseCache_time;
	std::chrono::milliseconds constructTour_time;
	std::chrono::milliseconds optimiseTour_time;
	double constructTour_distance;
};