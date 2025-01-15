#include "pch.h"
#include "gtest/gtest.h"
#include <tsp_template.h>

TEST(StaticLookahead, Similarity) {
	Square area = { {0, 0}, 1000, 1000 };
	std::mt19937 engine(1);

	auto cities = TspDataTemplate<Type2d, 50, CachingType::full, PartitioningType::quadTree>::generateCities(area, GenerationType::rectangle, engine);

	auto lookahead = std::make_unique<TspTemplate<Type2d, 50, CachingType::full, PartitioningType::linearSearch, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::None>>(area, cities)->run({1});
	auto linear = std::make_unique<TspTemplate<Type2d, 50, CachingType::full, PartitioningType::linearSearch, ConstructionType::ConvexHullInsertion, OptimisationType::None>>(area, cities)->run({});

	EXPECT_EQ(lookahead.route, linear.route);
}