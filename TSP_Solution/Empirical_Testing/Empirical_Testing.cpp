#include <iostream>
#include "tsp_template.h"

int main(int argc, char* argv[]) {
	const Square size = { { 0, 0}, 10, 10 };
	std::mt19937 e2(1);
	TspTemplate<Type2d, 100, CachingType::None, PartitioningType::NonePartitioning, ContructionType::LookaheadConvexHull, OptimisationType::kopt> tsp(size);
	tsp.run();
	auto route = tsp.getRoute();
	for (auto i : route) {
		std::cout << i << " ";
	}
	return 0;
}
