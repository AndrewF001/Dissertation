#pragma once
#include "test_class.h"

template<size_t size>
class BasicTest : public TestClass {
public:
	BasicTest(bool use_file) : TestClass("Basic" + std::to_string(size) + "Test", use_file) {};
	~BasicTest() = default;

	void Test() override {
		// Control
		const Square area = { {0, 0}, 1000, 1000 };

		auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
		unsigned int seed = std::chrono::duration_cast<std::chrono::microseconds>(now).count();

		std::mt19937 engine(seed);

		// Data for algorithm
		auto cities = TspDataTemplate<Type2d, size, CachingType::full, PartitioningType::quadTree>::generateCities(area, GenerationType::rectangle, engine);
		TSPArgs args;

		// Run algorithm
		auto ConvexHullInsertion = std::make_unique<TspTemplate<Type2d, size, CachingType::full, PartitioningType::quadTree, ConstructionType::ConvexHullInsertion, OptimisationType::TwoOpt>>(area, cities, GenerationType::rectangle, seed);
		addResult(ConvexHullInsertion->run(args));

		auto NearestNeighbour = std::make_unique<TspTemplate<Type2d, size, CachingType::full, PartitioningType::quadTree, ConstructionType::NearestNeighbour, OptimisationType::TwoOpt>>(area, cities, GenerationType::rectangle, seed);
		addResult(NearestNeighbour->run(args));

		auto ShortestInsertion = std::make_unique<TspTemplate<Type2d, size, CachingType::full, PartitioningType::quadTree, ConstructionType::ShortestInsertion, OptimisationType::TwoOpt>>(area, cities, GenerationType::rectangle, seed);
		addResult(ShortestInsertion->run(args));

		for (size_t i = 1; i < 9; i++) {
			args.max_depth = i;

			auto StaticLookahead = std::make_unique<TspTemplate<Type2d, size, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookahead, OptimisationType::TwoOpt>>(area, cities, GenerationType::rectangle, seed);
			addResult(StaticLookahead->run(args));

			auto StaticLookaheadConvexHullInserstion = std::make_unique<TspTemplate<Type2d, size, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::TwoOpt>>(area, cities, GenerationType::rectangle, seed);
			addResult(StaticLookaheadConvexHullInserstion->run(args));
		}
	};
};