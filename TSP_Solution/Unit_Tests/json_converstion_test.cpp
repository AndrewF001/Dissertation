#include "pch.h"
#include "gtest/gtest.h"
#include "file_handling/json_convertion.h"

TEST(JsonConversionTest, Point2DTest) {
	Point2D point = { 1, 2 };
	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Value val;

	jsonconversion::point2DToJSON(point, val, doc.GetAllocator());
	doc.AddMember("point", val, doc.GetAllocator());
	std::cout << jsonconversion::documentToString(doc) << "\n";
	auto p = jsonconversion::JSONToPoint2D(doc["point"]);
	
	EXPECT_EQ(point.m_x, p.m_x);
	EXPECT_EQ(point.m_y, p.m_y);
}

TEST(JsonConversionTest, SquareTest) {
	Square square = { {1, 2}, {3, 4} };
	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Value val;

	jsonconversion::squareToJSON(square, val, doc.GetAllocator());
	doc.AddMember("square", val, doc.GetAllocator());
	std::cout << jsonconversion::documentToString(doc) << "\n";
	auto s = jsonconversion::JSONToSquare(doc["square"]);

	EXPECT_EQ(square.m_p1.m_x, s.m_p1.m_x);
	EXPECT_EQ(square.m_p1.m_y, s.m_p1.m_y);
	EXPECT_EQ(square.m_p2.m_x, s.m_p2.m_x);
	EXPECT_EQ(square.m_p2.m_y, s.m_p2.m_y);
}