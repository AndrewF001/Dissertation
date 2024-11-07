#include <iostream>
#include <memory>
#include <chrono>
#include "tsp_template.h"

int main(int argc, char* argv[]) {
	auto start = std::chrono::high_resolution_clock::now();
	
	const Square area = {{0, 0}, 10, 10 };
	std::mt19937 engine(1);
	
	auto tsp = TspTemplate<Type2d, 10, CachingType::None, PartitioningType::NonePartitioning, ConstructionType::LookaheadConvexHull, OptimisationType::kopt>(area, GenerationType::Rectangle, engine);

	tsp.run(5);
	auto& route = tsp.getRoute();
	auto& data = tsp.getData();

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	
	printf("Time taken: %f seconds\n", duration.count() / 1000000.0);
	int i = 0;
	for (auto& point : data.getAllCities()) {
		std::cout << i++ << " : " << point.m_point << "\n";
	}
	
	for (auto i : route) {
		std::cout << i << " ";
	}
	return 0;
}
