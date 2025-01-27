#pragma once
#include "test_class.h"

class DynamicTest : public TestClass {
public:
	DynamicTest(bool use_file) : TestClass("DynamicTest", use_file) {};
	~MultiTest() = default;

	void Test() override {
		const Square area = { {0, 0}, 1000, 1000 };

		auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
		unsigned int seed = std::chrono::duration_cast<std::chrono::microseconds>(now).count();

		std::mt19937 engine(seed);

		auto cities = TspDataTemplate<Type2d, 100, CachingType::full, PartitioningType::quadTree>::generateCities(area, GenerationType::rectangle, engine);
		TSPArgs args;

		for (size_t i = 1; i < 9; i++) {
			args.max_depth = i;

			auto StaticLookahead = std::make_unique<TspTemplate<Type2d, 100, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookahead, OptimisationType::TwoOpt>>(area, cities, GenerationType::rectangle, seed);
			addResult(StaticLookahead->run(args));

			auto StaticLookaheadConvexHullInserstion = std::make_unique<TspTemplate<Type2d, 100, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::TwoOpt>>(area, cities, GenerationType::rectangle, seed);
			addResult(StaticLookaheadConvexHullInserstion->run(args));
		}

	};
};