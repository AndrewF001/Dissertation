#pragma once
#include "test_class.h"
#include "basic_test.h"

class MultiTest : public TestClass {
public:
	MultiTest(bool use_file, size_t max_size) : m_max_size(max_size), TestClass("MultiTest", use_file) {};
	~MultiTest() = default;

	void Test() override {
		if (m_max_size > 0)
			_test<SIZES[0]>();
		if (m_max_size > 1)
			_test<SIZES[1]>();
		if (m_max_size > 2)
			_test<SIZES[2]>();
		if (m_max_size > 3)
			_test<SIZES[3]>();
		if (m_max_size > 4)
			_test<SIZES[4]>();
		if (m_max_size > 5)
			_test<SIZES[5]>();
		if (m_max_size > 6)
			_test<SIZES[6]>();
		if (m_max_size > 7)
			_test<SIZES[7]>();
		if (m_max_size > 8)
			_test<SIZES[8]>();
		if (m_max_size > 9)
			_test<SIZES[9]>();
	};

private: 
	size_t m_max_size;

	template <size_t Size>
	void _test() {
		auto seed = Tester::seed_gen();
		auto cities = Tester::generateCities<Size>(seed);
		TSPArgs args;

		m_tester.TestAlgorithm<Size, ConstructionType::ConvexHullInsertion, OptimisationType::TwoOpt>(seed, cities, args);
		m_tester.TestAlgorithm<Size, ConstructionType::NearestNeighbour,OptimisationType::TwoOpt>(seed, cities, args);
		m_tester.TestAlgorithm<Size, ConstructionType::ShortestInsertion,OptimisationType::TwoOpt>(seed, cities, args);

		for (size_t i = 1; i < 9; i++) {
			args.max_depth = i;
			m_tester.TestAlgorithm<Size, ConstructionType::StaticLookahead,OptimisationType::TwoOpt>(seed, cities, args);
			m_tester.TestAlgorithm<Size, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::TwoOpt>(seed, cities, args);
		}
	}
};