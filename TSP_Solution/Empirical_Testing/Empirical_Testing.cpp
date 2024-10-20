#include "Compiled_TSP_Library.h"

int main(int argc, char* argv[]) {
	TSP_Data<Data_2d, CachingType::None, int> tsp_data;
	tsp_data.AddCity({0u});
	tsp_data.AddCity({1u});
	auto v = tsp_data.GetAllCities();
	std::cout << v.size();
	v[0].getDistance(v[1]);
}