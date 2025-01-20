#pragma once
#include "../test_class.h"

class Basic100Test : public TestClass {
public:
	Basic100Test(std::string n, size_t p = 1, std::chrono::seconds t = std::chrono::seconds::max()) : TestClass(n, p, t) {};
	~Basic100Test() = default;

	void Test() override {
		// Control
		const Square area = { {0, 0}, 1000, 1000 };

		//std::random_device r;
		//std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
		//std::mt19937 engine(seed);

		auto now = std::chrono::high_resolution_clock::now();
		auto duration = now.time_since_epoch();
		unsigned int seed = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

		std::mt19937 engine(seed);

		// Data for algorithm
		auto cities = TspDataTemplate<Type2d, 100, CachingType::full, PartitioningType::quadTree>::generateCities(area, GenerationType::rectangle, engine);
		TSPArgs args;

		// Run algorithm
		TspTemplate<Type2d, 100, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::TwoOpt>tsp(area, cities, GenerationType::rectangle, seed);
		addResult(tsp.run(args));
	};
};