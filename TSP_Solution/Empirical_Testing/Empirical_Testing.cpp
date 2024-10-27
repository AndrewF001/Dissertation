//#include "tsp_library_realtime.h"
#include <iostream>
#include "tsp_template.h"

int main(int argc, char* argv[]) {
	Cube size = { { 10, 10, 10 }, 10, 10, 10 };
	TspTemplate<Type2d, CachingType::None, int> T(size);
	T.m_data.addCity({2, 2, 2});
	T.m_data.addCity({0, 0, 0});
	std::mt19937 e2(1);
	T.m_data.generateRandomCities(GenerationType::Rectangle, {1, 1, 1}, e2);
	T.m_data.generateRandomCities(GenerationType::Rectangle, {1, 1, 1}, e2);
	auto v = T.m_data.getAllCities();
	for(auto& elm : v) {
		std::cout << elm.m_point << "\n";
	}
	std::cout << v[2].getDistance(v[3]);
}