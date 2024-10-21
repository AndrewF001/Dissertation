#include "Compiled_TSP_Library.h"
#include "Runtime_TSP_Library.h"

int main(int argc, char* argv[]) {
	
	T_TSP< Data_2d, CachingType::None, int> T;
	T.t.AddCity({0u});
	T.t.AddCity({1u});
	auto v = T.t.GetAllCities();
	std::cout << v.size();
	v[0].getDistance(v[1]);
	
	//R_TSP r;
	//r.data.GetNumberOfCities();
	//r.data.AddCity(0);
	//r.data.AddCity(1);
	/*auto v2 = r.data.GetAllCities();
	std::cout << v2.size();
	v2[0]->getDistance(*v2[1]);*/
	
}