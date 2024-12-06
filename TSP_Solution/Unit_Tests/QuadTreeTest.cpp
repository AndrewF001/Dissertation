#include "pch.h"
#include "gtest/gtest.h"
#include "tsp_data/partitioning/quadtree.h"

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
	std::vector<cityID> expect = { 0, 1, 4, 3, 2 };
	EXPECT_EQ(found.size(), 5);
	EXPECT_EQ(found, expect);
}

TEST(QuadTreeTest, DepthInsertion) {
	QuadTree tree(Square{ {0, 0}, 100, 100 });
	tree.insert(0, Point2D{ 60, 60 });	// Root
	tree.insert(1, Point2D{ 30, 30 });	// Top left
	tree.insert(2, Point2D{ 20, 20 });  // Top left
	tree.insert(3, Point2D{ 10, 10 });	// Top left
	tree.insert(4, Point2D{ 5, 5 });	// Top left

	auto found = tree.contains(Square{ {0, 0}, 100, 100 });
	std::vector<cityID> expect = { 0, 1, 2, 3, 4 };
	EXPECT_EQ(found.size(), 5);
	EXPECT_EQ(found, expect);
}

TEST(QuadTreeTest, BasicSearch) {
	QuadTree tree(Square{ {0, 0}, 100, 100 });
	tree.insert(0, Point2D{ 60, 60 }); // Root
	tree.insert(1, Point2D{ 30, 30 }); // Top left
	tree.insert(2, Point2D{ 70, 70 }); // Bottom right
	tree.insert(3, Point2D{ 30, 70 }); // Bottom left
	tree.insert(4, Point2D{ 70, 30 }); // Top right

	auto found = tree.contains(Square{ {0, 0}, 40, 40 });
	std::vector<cityID> expect = { 0, 1};
	EXPECT_EQ(found.size(), 2);
	EXPECT_EQ(found, expect);
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
	std::vector<cityID> expect = { 0, 1, 7, 6  };
	EXPECT_EQ(found.size(), 4);
	EXPECT_EQ(found, expect);
}