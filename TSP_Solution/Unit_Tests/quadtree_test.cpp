#include "pch.h"
#include "gtest/gtest.h"
#include <memory>
#include "tsp_data/partitioning/quadtree.h"
#include <tsp_template.h>


static void check_result(const std::vector<cityID>& found, const std::vector<cityID> expect) {
	EXPECT_EQ(found.size(), expect.size());
	EXPECT_EQ(found, expect);
}

TEST(QuadTreeTest, Creation) {
	QuadTree tree(Square{ {0, 0}, 100, 100 });

	auto found = tree.contains(Square{ {0, 0}, 100, 100 });

	EXPECT_EQ(found, std::vector<cityID>{});
}

TEST(QuadTreeTest, SingleInsertion) {
	QuadTree tree(Square{ {0, 0}, 100, 100 });
	tree.insert(15, Point2D{ 50, 50 });
	
	auto found = tree.contains(Square{ {0, 0}, 100, 100 });
	EXPECT_EQ(found, std::vector<cityID>{15});
}

TEST(QuadTreeTest, MultipleInsertion) {
	QuadTree tree(Square{ {0, 0}, 100, 100 });
	tree.insert(0, Point2D{ 60, 60 }); // Root
	tree.insert(1, Point2D{ 30, 30 }); // Top left
	tree.insert(2, Point2D{ 70, 70 }); // Bottom right
	tree.insert(3, Point2D{ 30, 70 }); // Bottom left
	tree.insert(4, Point2D{ 70, 30 }); // Top right

	auto found = tree.contains(Square{ {0, 0}, 100, 100 });
	check_result(found, { 0, 1, 4, 3, 2 });
}

TEST(QuadTreeTest, DepthInsertion) {
	QuadTree tree(Square{ {0, 0}, 100, 100 });
	tree.insert(0, Point2D{ 60, 60 });	// Root
	tree.insert(1, Point2D{ 30, 30 });	// Top left
	tree.insert(2, Point2D{ 20, 20 });  // Top left
	tree.insert(3, Point2D{ 10, 10 });	// Top left
	tree.insert(4, Point2D{ 5, 5 });	// Top left

	auto found = tree.contains(Square{ {0, 0}, 100, 100 });
	check_result(found, { 0, 1, 2, 3, 4 });
}

TEST(QuadTreeTest, BasicSearch) {
	QuadTree tree(Square{ {0, 0}, 100, 100 });
	tree.insert(0, Point2D{ 60, 60 }); // Root
	tree.insert(1, Point2D{ 30, 30 }); // Top left
	tree.insert(2, Point2D{ 70, 70 }); // Bottom right
	tree.insert(3, Point2D{ 30, 70 }); // Bottom left
	tree.insert(4, Point2D{ 70, 30 }); // Top right

	auto found = tree.contains(Square{ {0, 0}, 40, 40 });
	check_result(found, { 1 });
}

TEST(QuadTreeTest, DepthSearch) {
	QuadTree tree(Square{ {0, 0}, 100, 100 });
	tree.insert(0, Point2D{ 60, 60 }); // Root
	tree.insert(1, Point2D{ 30, 30 }); // Top left
	tree.insert(2, Point2D{ 70, 70 }); // Bottom right
	tree.insert(3, Point2D{ 30, 70 }); // Bottom left
	tree.insert(4, Point2D{ 70, 30 }); // Top right
	tree.insert(6, Point2D{ 30, 30 });	// Top left
	tree.insert(7, Point2D{ 20, 20 });  // Top left
	tree.insert(8, Point2D{ 10, 10 });	// Top left
	tree.insert(9, Point2D{ 5, 5 });	// Top left

	auto found = tree.contains(Square{ {20, 20}, 20, 20 });
	check_result(found, { 1, 7, 6 });
}

TEST(QuadTreeTest, StaticLookahead) {
	Square area = { {0, 0}, 1000, 1000 };
	std::mt19937 engine(1);
	constexpr size_t size = 50;

	auto cities = TspDataTemplate<Type2d, size, CachingType::full, PartitioningType::quadTree>::generateCities(area, GenerationType::rectangle, engine);

	auto quad = std::make_unique<TspTemplate<Type2d, size, CachingType::full, PartitioningType::quadTree, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::TwoOpt>>(area, cities)->run(2);
	auto linear = std::make_unique<TspTemplate<Type2d, size, CachingType::full, PartitioningType::linearSearch, ConstructionType::StaticLookaheadConvexHullInserstion, OptimisationType::TwoOpt>>(area, cities)->run(2);

	EXPECT_EQ(quad.route, linear.route);
}

TEST(QuadTreeTest, StaticNearestNeighbour) {
	Square area = { {0, 0}, 1000, 1000 };
	std::mt19937 engine(1);

	auto cities = TspDataTemplate<Type2d, 50, CachingType::full, PartitioningType::quadTree>::generateCities(area, GenerationType::rectangle, engine);

	auto quad = std::make_unique<TspTemplate<Type2d, 50, CachingType::full, PartitioningType::quadTree, ConstructionType::NearestNeighbour, OptimisationType::TwoOpt>>(area, cities)->run(2);
	auto linear = std::make_unique<TspTemplate<Type2d, 50, CachingType::full, PartitioningType::linearSearch, ConstructionType::NearestNeighbour, OptimisationType::TwoOpt>>(area, cities)->run(2);

	EXPECT_EQ(quad.route, linear.route);
}

TEST(QuadTreeTest, ClostestInerstion) {
	Square area = { {0, 0}, 1000, 1000 };
	std::mt19937 engine(1);

	auto cities = TspDataTemplate<Type2d, 50, CachingType::full, PartitioningType::quadTree>::generateCities(area, GenerationType::rectangle, engine);

	auto quad = std::make_unique<TspTemplate<Type2d, 50, CachingType::full, PartitioningType::quadTree, ConstructionType::ShortestInsertion, OptimisationType::TwoOpt>>(area, cities)->run(2);
	auto linear = std::make_unique<TspTemplate<Type2d, 50, CachingType::full, PartitioningType::linearSearch, ConstructionType::ShortestInsertion, OptimisationType::TwoOpt>>(area, cities)->run(2);

	EXPECT_EQ(quad.route, linear.route);
}

TEST(QuadTreeTest, ConvexHull) {
	Square area = { {0, 0}, 1000, 1000 };
	std::mt19937 engine(1);

	auto cities = TspDataTemplate<Type2d, 50, CachingType::full, PartitioningType::quadTree>::generateCities(area, GenerationType::rectangle, engine);

	auto quad = std::make_unique<TspTemplate<Type2d, 50, CachingType::full, PartitioningType::quadTree, ConstructionType::ConvexHullInsertion, OptimisationType::TwoOpt>>(area, cities)->run(2);
	auto linear = std::make_unique<TspTemplate<Type2d, 50, CachingType::full, PartitioningType::linearSearch, ConstructionType::ConvexHullInsertion, OptimisationType::TwoOpt>>(area, cities)->run(2);

	EXPECT_EQ(quad.route, linear.route);
}
