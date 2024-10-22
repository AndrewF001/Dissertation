#include "tsp_library_realtime.h"
#include "tsp_library_template.h"

int main(int argc, char* argv[]) {
	
	TspTemplate<Type2d, CachingType::None, int> T;
	T.t.addCity({0u});
	T.t.addCity({1u});
	auto v = T.t.getAllCities();
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