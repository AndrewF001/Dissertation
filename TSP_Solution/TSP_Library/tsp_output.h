#pragma once
#include "tsp_data/tsp_constructs.h"
#include <vector>
struct TSPOutput {
	// .tsp file data fields
	std::string name;	// File name
	std::string type;	// Type of TSP
	std::string comment;
	size_t dimension;	// Number of cities
	std::string edge_weight_type;	// Type of data used for edge weights
	std::string display_data_type;
	std::vector<Point2D> node_coord_section;

	Square area;

	// Completed route
	double distance;
	std::vector<cityID> route;

	// Run statistics
	double run_time;
	double initalisePartition;
	double initaliseCache;
	double constructTour;
	double optimiseTour;
};