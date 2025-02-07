#include "pch.h"
#include "gtest/gtest.h"
#include <tsp_template.h>

TEST(DynamicLookaheadTest, depths) {
	DynamicArgs args;

	auto r = DynamicLookahead<Type2d, 10, CachingType::full, PartitioningType::quadTree>::optimalDepth(10, 10, args);
	EXPECT_EQ(r, 1);

	r = DynamicLookahead<Type2d, 20, CachingType::full, PartitioningType::quadTree>::optimalDepth(20, 10, args);
	EXPECT_EQ(r, 2);

	r = DynamicLookahead<Type2d, 40, CachingType::full, PartitioningType::quadTree>::optimalDepth(40, 10, args);
	EXPECT_EQ(r, 3);

	r = DynamicLookahead<Type2d, 100, CachingType::full, PartitioningType::quadTree>::optimalDepth(100, 10, args);
	EXPECT_EQ(r, 4);

	r = DynamicLookahead<Type2d, 300, CachingType::full, PartitioningType::quadTree>::optimalDepth(300, 10, args);
	EXPECT_EQ(r, 5);

	r = DynamicLookahead<Type2d, 600, CachingType::full, PartitioningType::quadTree>::optimalDepth(500, 10, args);
	EXPECT_EQ(r, 6);

	r = DynamicLookahead<Type2d, 1000, CachingType::full, PartitioningType::quadTree>::optimalDepth(1000, 10, args);
	EXPECT_EQ(r, 7);
}