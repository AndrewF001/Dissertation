#pragma once
#include "test_class.h"
#include "basic_test.h"

class DynamicArgsTest : public TestClass {
public:
	DynamicArgsTest(bool use_file, size_t max_size) : m_max_size(max_size), TestClass("DynamicArgsTest", use_file) {};
	~DynamicArgsTest() = default;

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

		const DynamicArgs BASE;
		DynamicArgs gaps;
		gaps.constant = 0.2;
		gaps.logrithm = 0.05;
		gaps.multiplier = 0.1;

		args.max_depth = 8;
		args.dynamic_args = BASE;

		// Base Case
		m_tester.TestDynamicLookahead<Size, OptimisationType::TwoOpt>(seed, cities, args);
		m_tester.TestDynamicLookaheadConvexHullInserstion<Size, OptimisationType::TwoOpt>(seed, cities, args);

		// Constant change
		for (int i = -2; i <= 2; i++) {
			if (i == 0)
				continue;

			args.dynamic_args.constant = BASE.constant + (i * gaps.constant);
			m_tester.TestDynamicLookahead<Size, OptimisationType::TwoOpt>(seed, cities, args);
			m_tester.TestDynamicLookaheadConvexHullInserstion<Size, OptimisationType::TwoOpt>(seed, cities, args);
		}

		args.dynamic_args.constant = BASE.constant;

		// Logirithm change
		for (int i = -2; i <= 2; i++) {
			if (i == 0)
				continue;

			args.dynamic_args.logrithm = BASE.logrithm + (i * gaps.logrithm);
			m_tester.TestDynamicLookahead<Size, OptimisationType::TwoOpt>(seed, cities, args);
			m_tester.TestDynamicLookaheadConvexHullInserstion<Size, OptimisationType::TwoOpt>(seed, cities, args);
		}

		args.dynamic_args.logrithm = BASE.logrithm;

		// Multiplier change
		for (int i = -2; i <= 2; i++) {
			if (i == 0)
				continue;

			args.dynamic_args.multiplier = BASE.multiplier + (i * gaps.multiplier);
			m_tester.TestDynamicLookahead<Size, OptimisationType::TwoOpt>(seed, cities, args);
			m_tester.TestDynamicLookaheadConvexHullInserstion<Size, OptimisationType::TwoOpt>(seed, cities, args);
		}
	}
};
