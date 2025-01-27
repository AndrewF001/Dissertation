#pragma once
#include "test_class.h"
#include "basic_test.h"

class MultiTest : public TestClass {
public:
	MultiTest(bool use_file, size_t max_size) : m_max_size(max_size), TestClass("MultiTest", use_file) {};
	~MultiTest() = default;

	void Test() override {
		std::vector<std::thread> threads;

		if (m_max_size > 0)
			threads.emplace_back([this]() { _test<SIZES[0]>(); });
		if (m_max_size > 1)
			threads.emplace_back([this]() { _test<SIZES[1]>(); });
		if (m_max_size > 2)
			threads.emplace_back([this]() { _test<SIZES[2]>(); });
		if (m_max_size > 3)
			threads.emplace_back([this]() { _test<SIZES[3]>(); });
		if (m_max_size > 4)
			threads.emplace_back([this]() { _test<SIZES[4]>(); });
		if (m_max_size > 5)
			threads.emplace_back([this]() { _test<SIZES[5]>(); });
		if (m_max_size > 6)
			threads.emplace_back([this]() { _test<SIZES[6]>(); });
		if (m_max_size > 7)
			threads.emplace_back([this]() { _test<SIZES[7]>(); });
		if (m_max_size > 8)
			threads.emplace_back([this]() { _test<SIZES[8]>(); });
		if (m_max_size > 9)
			threads.emplace_back([this]() { _test<SIZES[9]>(); });

		for (auto& thread : threads) {
			if (thread.joinable()) {
				thread.join();
			}
		}
	};

private: 
	size_t m_max_size;

	template <size_t Size>
	void _test() {
		auto seed = Tests::seed_gen();
		auto cities = Tests::generateCities<Size>(seed);
		TSPArgs args;

		addResult(Tests::TestConvexHullInsertion<Size, OptimisationType::TwoOpt>(seed, cities, args));
		addResult(Tests::TestNearestNeighbour<Size, OptimisationType::TwoOpt>(seed, cities, args));
		addResult(Tests::TestShortestInsertion<Size, OptimisationType::TwoOpt>(seed, cities, args));

		for (size_t i = 1; i < 9; i++) {
			args.max_depth = i;
			addResult(Tests::TestStaticLookahead<Size, OptimisationType::TwoOpt>(seed, cities, args));
			addResult(Tests::TestStaticLookaheadConvexHullInserstion<Size, OptimisationType::TwoOpt>(seed, cities, args));
		}
	}
};