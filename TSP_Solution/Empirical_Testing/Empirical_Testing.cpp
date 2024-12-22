#include <iostream>
#include <memory>
#include <chrono>
#include "tsp_template.h"

#include "logger.h"
#include <tsp_file.h>

int main(int argc, char* argv[]) {
	const Square area = {{0, 0}, 1000, 1000 };
	std::mt19937 engine(1);
	
	auto tsp = std::make_unique<TspTemplate<Type2d, 100, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::TwoOpt>>(area, GenerationType::rectangle, engine);

	auto output = tsp->run(2);
	
	Logger::log("Time taken: " + std::to_string(output.total_run_time.count() / 1000000.0) + " seconds\n");

	TSPFile file("test.bin");
	file.addEntry(output);



	if (output.validRoute) {
		Logger::log("Route is valid\n");
	}
	else {
		Logger::log("Invalid route!!!\n");
	}

	for (cityID i = 0; i < output.num_cities; i++) {
		std::stringstream s;
		s << i << " : " << output.node_coord_section[i] << "\n";
		Logger::log(s);
	}
	
	for (auto i : output.route) {
		Logger::log( std::to_string(i) + " ");
	}
	return 0;
}
