#include <iostream>
#include "tsp_template.h"

int main(int argc, char* argv[]) {
	Cube size = { { 10, 10, 10 }, 10, 10, 10 };
	TspTemplate<Type2d, 4, CachingTypes::None, NoPartitioning<Type2d,4>,
		LookaheadConvexHull<Type2d, 4, CachingTypes::None, NoPartitioning<Type2d, 4>>,
		Kopt<Type2d, 4, CachingTypes::None, NoPartitioning<Type2d, 4>>> tsp(size);
	tsp.m_data.addCity({2, 2, 2});
	tsp.m_data.addCity({0, 0, 0});
	std::mt19937 e2(1);
	tsp.m_data.generateRandomCities(GenerationTypes::Rectangle, {1, 1, 1}, e2);
	tsp.m_data.generateRandomCities(GenerationTypes::Rectangle, {1, 1, 1}, e2);
	auto v = tsp.m_data.getAllCities();
	for(auto& elm : v) {
		std::cout << elm.m_point << "\n";
	}
	std::cout << v[2].getDistance(v[3]) << "\n";
	tsp.m_construction.constructTour();
	tsp.m_optimisation.optimiseTour();

	tsp.run();
	std::cout << tsp.m_data.getDistance(0, 1) << "\n";
}
