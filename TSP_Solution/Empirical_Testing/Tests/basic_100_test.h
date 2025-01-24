#pragma once
#include "test_class.h"

class Basic100Test : public TestClass {
public:
	Basic100Test(bool use_file) : TestClass("Basic100Test", use_file) {};
	~Basic100Test() = default;

	void Test() override {
		// Control
		const Square area = { {0, 0}, 1000, 1000 };

		auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
		unsigned int seed = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

		std::mt19937 engine(seed);

		// Data for algorithm
		auto cities = TspDataTemplate<Type2d, 100, CachingType::full, PartitioningType::quadTree>::generateCities(area, GenerationType::rectangle, engine);
		TSPArgs args;

		// Run algorithm
		auto tsp = std::make_unique<TspTemplate<Type2d, 100, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::TwoOpt>>(area, cities, GenerationType::rectangle, seed);
		addResult(tsp->run(args));
	};
};