#pragma once
#include "test_class.h"

template<size_t Size, OptimisationType Opt>
class BasicTest : public TestClass {
public:
	BasicTest(bool use_file) : TestClass("Basic" + std::to_string(Size) + "Test", use_file) {};
	~BasicTest() = default;

	void Test() override {
		// Control
		auto seed = Tests::seed_gen();
		auto cities = Tests::generateCities<Size>(seed);
		TSPArgs args;

		addResult(Tests::TestConvexHullInsertion<Size, Opt>(seed, cities, args));
		addResult(Tests::TestNearestNeighbour<Size, Opt>(seed, cities, args));
		addResult(Tests::TestShortestInsertion<Size, Opt>(seed, cities, args));

		for (size_t i = 1; i < 9; i++) {
			args.max_depth = i;
			addResult(Tests::TestStaticLookahead<Size, Opt>(seed, cities, args));
			addResult(Tests::TestStaticLookaheadConvexHullInserstion<Size, Opt>(seed, cities, args));
		}
	};

};