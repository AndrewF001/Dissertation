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

		m_tester.TestAlgorithm<Size, ConstructionType::ConvexHullInsertion, Opt>(seed, cities, args);
		m_tester.TestAlgorithm<Size, ConstructionType::NearestNeighbour, Opt>(seed, cities, args);
		m_tester.TestAlgorithm<Size, ConstructionType::ShortestInsertion ,Opt>(seed, cities, args);

		for (size_t i = 1; i < 9; i++) {
			args.max_depth = i;
#ifndef DEMONSTRATION
			m_tester.TestAlgorithm<Size, ConstructionType::StaticLookahead, Opt>(seed, cities, args);
#endif
			m_tester.TestAlgorithm<Size, ConstructionType::StaticLookaheadConvexHullInserstion, Opt>(seed, cities, args);
		}
#ifndef DEMONSTRATION
		m_tester.TestAlgmorithm<Size, ConstructionType::DynamicLookahead, Opt>(seed, cities, args);
#endif
		m_tester.TestAlgorithm<Size, ConstructionType::DynamicLookaheadConvexHullInserstion, Opt>(seed, cities, args);
	};

};