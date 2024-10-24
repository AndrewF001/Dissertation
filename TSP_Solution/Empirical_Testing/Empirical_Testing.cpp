//#include "tsp_library_realtime.h"
#include "tsp_library_template.h"
#include <iostream>

int main(int argc, char* argv[]) {
	
	TspTemplate<Type2d, CachingType::None, int> T;
	T.t.addCity({2, 2, 2});
	T.t.addCity({0, 0, 0});
	std::mt19937 e2(1);
	T.t.generateRandomCities(GenerationType::Rectangle, {1, 1, 1}, e2);
	T.t.generateRandomCities(GenerationType::Rectangle, {1, 1, 1}, e2);
	auto v = T.t.getAllCities();
	for(auto& elm : v) {
		std::cout << elm.m_point << "\n";
	}
	std::cout << v[2].getDistance(v[3]);
	
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