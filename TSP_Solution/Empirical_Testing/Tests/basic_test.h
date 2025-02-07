#pragma once
#include "test_class.h"

template<size_t Size, OptimisationType Opt>
class BasicTest : public TestClass {
public:
	BasicTest(bool use_file) : TestClass("Basic" + std::to_string(Size) + "Test", use_file) {};
	~BasicTest() = default;

	void Test() override {
		// Control
		auto seed = Tester::seed_gen();
		auto cities = Tester::generateCities<Size>(seed);
		TSPArgs args;

		m_tester.TestConvexHullInsertion<Size, Opt>(seed, cities, args);
		m_tester.TestNearestNeighbour<Size, Opt>(seed, cities, args);
		m_tester.TestShortestInsertion<Size, Opt>(seed, cities, args);

		for (size_t i = 1; i < 9; i++) {
			args.max_depth = i;
			m_tester.TestStaticLookahead<Size, Opt>(seed, cities, args);
			m_tester.TestStaticLookaheadConvexHullInserstion<Size, Opt>(seed, cities, args);
		}
	};

};