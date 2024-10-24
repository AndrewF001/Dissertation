//#include "tsp_library_realtime.h"
#include "tsp_library_template.h"
#include <iostream>

int main(int argc, char* argv[]) {
	
	TspTemplate<Type2d, CachingType::None, int> T;
	T.t.addCity({0u, {}});
	T.t.addCity({1u, {}});
	auto v = T.t.getAllCities();
	std::cout << v.size();
	v[0].getDistance(v[1]);
	
	/*
	TspRealtime r;
	std::cout << "\n" << r.data.getNumberOfCities();
	r.data.addCity(0);
	r.data.addCity(1);
	auto v2 = r.data.getAllCities();
	std::cout << v2->size();
	*/
	//v2[0]->getDistance(*v2[1]);
	
}