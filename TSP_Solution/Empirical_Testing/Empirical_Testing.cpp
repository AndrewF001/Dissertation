#include <iostream>
#include "tsp_template.h"

int main(int argc, char* argv[]) {
	const Square size = { { 0, 0}, 10, 10 };
	std::mt19937 e2(1);
	TspTemplate<Type2d, 4, CachingType::None, PartitioningType::NonePartitioning, ContructionType::LookaheadConvexHull, OptimisationType::kopt> tsp(size);
	/*tsp.m_data.addCity({2, 2});
	tsp.m_data.addCity({0, 0});
	tsp.m_data.generateRandomCities(GenerationType::Rectangle, e2);
	tsp.m_data.generateRandomCities(GenerationType::Rectangle, e2);

	auto v = tsp.m_data.getAllCities();
	for (auto& elm : v) {
		std::cout << elm.m_point << "\n";
	}

	auto test = tsp.m_data.getCities({{ 0, 0}, 10, 10});

	std::cout << test.size() << "\n";
	std::cout << tsp.m_data.getDistance(test.at(2), test.at(1)) << " new code\n";
	*/
	tsp.run();
	tsp.getData();
}
