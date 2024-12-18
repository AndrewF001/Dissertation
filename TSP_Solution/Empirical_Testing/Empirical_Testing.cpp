#include <iostream>
#include <memory>
#include <chrono>
#include "tsp_template.h"

int main(int argc, char* argv[]) {
	
	const Square area = {{0, 0}, 1000, 1000 };
	std::mt19937 engine(1);
	
	auto tsp = std::make_unique<TspTemplate<Type2d, 1000, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::TwoOpt>>(area, GenerationType::rectangle, engine);

	auto output = tsp->run(5);
	
	printf("Time taken: %f seconds\n", output.total_run_time.count() / 1000000.0);

	if (output.validRoute) {
		std::cout << "Route is valid\n";
	}
	else {
		std::cout << "Invalid route!!!\n";
	}

	for (cityID i = 0; i < output.num_cities; i++) {
		std::cout << i << " : " << output.node_coord_section[i] << "\n";
	}
	
	for (auto i : output.route) {
		std::cout << i << " ";
	}
	return 0;
}
