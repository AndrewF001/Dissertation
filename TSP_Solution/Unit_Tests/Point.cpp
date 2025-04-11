#include "pch.h"
#include "gtest/gtest.h"
#include <tsp_data/types/2d.h>


TEST(PointTest, Creation) {
	Point2D p1{ 0, 0 };
	EXPECT_EQ(p1.m_x, 0);
	EXPECT_EQ(p1.m_y, 0);

	Point2D p2{ 10, 10 };
	EXPECT_EQ(p2.m_x, 10);
	EXPECT_EQ(p2.m_y, 10);
}

TEST(PointTest, Gradient) {
	Point2D p1{ 0, 0 };
	Point2D p2{ 10, 10 };
	Point2D p3{ 10, 0 };
	Point2D p4{ 0, 10 };
	Point2D p5{ -10, -10 };

	EXPECT_EQ(p1.gradient(p2), 1);	// Positive slope
	EXPECT_EQ(p1.gradient(p5), 1);	// Same slop reverse position
	EXPECT_EQ(p1.gradient(p3), 0);  // Horizontal line
	EXPECT_EQ(p1.gradient(p4), INFINITY); // Virtical line
}