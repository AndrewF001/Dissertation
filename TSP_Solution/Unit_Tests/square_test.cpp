#include "pch.h"
#include "gtest/gtest.h"
#include "tsp_data/tsp_constructs.h"

TEST(SquareTest, Creation) {
	Square s{ {0, 0}, 100, 100 };

	EXPECT_EQ(s.m_p1.m_x, 0);
	EXPECT_EQ(s.m_p1.m_y, 0);
	EXPECT_EQ(s.m_p2.m_x, 100);
	EXPECT_EQ(s.m_p2.m_y, 100);
}

TEST(SquareTest, Contains) {
	Square s{ {0, 0}, 100, 100 };

	Point2D p1{ 50, 50 };	// Middle
	EXPECT_TRUE(s.contains(p1));

	Point2D p2{ 0, 0 };		// Boundary
	EXPECT_TRUE(s.contains(p2));

	Point2D p3{ 100, 100 };	// Boundary
	EXPECT_TRUE(s.contains(p3));

	Point2D p4{ -1, 0 };	// Outside
	EXPECT_FALSE(s.contains(p4));

	Point2D p5{ 101, 0 };	// Outside
	EXPECT_FALSE(s.contains(p5));

	Point2D p6{ 0, -1 };	// Outside
	EXPECT_FALSE(s.contains(p6));

	Point2D p7{ 0, 101 };	// Outside
	EXPECT_FALSE(s.contains(p7));
}

TEST(SquareTest, Overlap) {
	Square s{ {0, 0}, 100, 100 };
	
	Square s2{ {40, 40}, 20, 20 };	// Inside
	EXPECT_TRUE(s.overlaps(s2));
	EXPECT_TRUE(s2.overlaps(s));

	Square s3{ {0, 0}, 100, 100 };  // Same
	EXPECT_TRUE(s.overlaps(s3));
	EXPECT_TRUE(s3.overlaps(s));

	Square s4{ {-1, -1}, 2, 2 };	// Outside-in
	EXPECT_TRUE(s.overlaps(s4));
	EXPECT_TRUE(s4.overlaps(s));

	Square s5{ {99, 99}, 2, 2 };	// Inside-out
	EXPECT_TRUE(s.overlaps(s5));
	EXPECT_TRUE(s5.overlaps(s));

	Square s9 { {0, 0}, 0, 0 };	// Same
	EXPECT_TRUE(s.overlaps(s9));
	EXPECT_TRUE(s9.overlaps(s));

	Square s6{ {100, 100}, 0, 0 };	// Boundary
	EXPECT_TRUE(s.overlaps(s6));
	EXPECT_TRUE(s6.overlaps(s));
	
	Square s7{ {-1, -1}, 0, 0 };	// Outside
	EXPECT_FALSE(s.overlaps(s7));
	EXPECT_FALSE(s7.overlaps(s));
	
	Square s8{ {101, 101}, 1, 1 };	// Outside
	EXPECT_FALSE(s.overlaps(s8));
	EXPECT_FALSE(s8.overlaps(s));
}