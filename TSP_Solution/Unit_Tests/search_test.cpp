#include "pch.h"
#include "gtest/gtest.h"
#include "tsp_data/tsp_data_template.h"
#include <tsp_data/types/2d.h>

template <typename T>
void compareVector(const std::vector<T>& a, const std::vector<T> b) {
	EXPECT_EQ(a.size(), b.size());
	for (size_t i = 0; i < a.size(); i++) {
		EXPECT_EQ(a[i], b[i]);
	}
}

template <typename T>
void vectorContains(const std::vector<T>& a, const std::vector<T> b) {
	EXPECT_EQ(a.size(), b.size());
	for (size_t i = 0; i < b.size(); i++) {
		EXPECT_TRUE(std::count(a.begin(), a.end(), b[i]));
	}
}

TEST(SearchArea, LinearSearch) {
	const Square s{ {0, 0}, 100, 100 };
	std::mt19937 e(1);
	TspDataTemplate<Type2d, 10, CachingType::full, PartitioningType::linearSearch> data(s, GenerationType::rectangle, e);

	for (size_t i = 0; i < 10; i++) {
		std::cout << i  << data.getCityPoint(i) << "\n";
	}

	/*
	6Point2D(22.9577, 44.3453)
	2Point2D(39.6581, 23.6089)
	8Point2D(43.0699, 45.7205)
	5Point2D(52.4548, 31.3274)
	3Point2D(66.9746, 38.7911)
	9Point2D(77.8389, 93.9128)
	4Point2D(84.6311, 93.5539)
	7Point2D(91.3962, 53.4414)
	0Point2D(93.2557, 99.7185)
	1Point2D(99.9041, 12.8124)
	*/

	EXPECT_EQ(data.getNumberOfCities(), 10);

	auto res = data.getCitiesInArea(Square{ {0, 0}, 100, 100 });
	EXPECT_EQ(res.size(), 10);
	compareVector(res, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

	res = data.getCitiesInArea(Square{ {23, 0}, 100, 100 });
	EXPECT_EQ(res.size(), 9);
	compareVector(res, { 0, 1, 2, 3, 4, 5, 7, 8, 9 });

	res = data.getCitiesInArea(Square{ {0, 0}, 94, 100 });
	EXPECT_EQ(res.size(), 9);
	compareVector(res, { 0, 2, 3, 4, 5, 6, 7, 8, 9 });

	res = data.getCitiesInArea(Square{ {0, 13}, 100, 100 });
	EXPECT_EQ(res.size(), 9);
	compareVector(res, { 0, 2, 3, 4, 5, 6, 7, 8, 9 });

	res = data.getCitiesInArea(Square{ {0, 0}, 100, 95 });
	EXPECT_EQ(res.size(), 9);
	compareVector(res, { 1, 2, 3, 4, 5, 6, 7, 8 ,9 });

	res = data.getCitiesInArea(Square{ {0, 0}, 1, 1 });
	EXPECT_EQ(res.size(), 0);
	compareVector(res, {});

	res = data.getCitiesInArea(Square{ {40, 40}, 20, 20 });
	EXPECT_EQ(res.size(), 1);
	compareVector(res, { 8 });
}

TEST(SearchArea, QuadSearch) {
	const Square s{ {0, 0}, 100, 100 };
	std::mt19937 e(1);
	TspDataTemplate<Type2d, 10, CachingType::full, PartitioningType::quadTree> data(s, GenerationType::rectangle, e);
	data.initalisePartition();

	/*
	6Point2D(22.9577, 44.3453)
	2Point2D(39.6581, 23.6089)
	8Point2D(43.0699, 45.7205)
	5Point2D(52.4548, 31.3274)
	3Point2D(66.9746, 38.7911)
	9Point2D(77.8389, 93.9128)
	4Point2D(84.6311, 93.5539)
	7Point2D(91.3962, 53.4414)
	0Point2D(93.2557, 99.7185)
	1Point2D(99.9041, 12.8124)
	*/

	EXPECT_EQ(data.getNumberOfCities(), 10);

	auto res = data.getCitiesInArea(Square{ {0, 0}, 100, 100 });
	EXPECT_EQ(res.size(), 10);
	vectorContains(res, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

	res = data.getCitiesInArea(Square{ {23, 0}, 100, 100 });
	EXPECT_EQ(res.size(), 9);
	vectorContains(res, { 0, 1, 2, 3, 4, 5, 7, 8, 9 });

	res = data.getCitiesInArea(Square{ {0, 0}, 94, 100 });
	EXPECT_EQ(res.size(), 9);
	vectorContains(res, { 0, 2, 3, 4, 5, 6, 7, 8, 9 });

	res = data.getCitiesInArea(Square{ {0, 13}, 100, 100 });
	EXPECT_EQ(res.size(), 9);
	vectorContains(res, { 0, 2, 3, 4, 5, 6, 7, 8, 9 });

	res = data.getCitiesInArea(Square{ {0, 0}, 100, 95 });
	EXPECT_EQ(res.size(), 9);
	vectorContains(res, { 1, 2, 3, 4, 5, 6, 7, 8 ,9 });

	res = data.getCitiesInArea(Square{ {0, 0}, 1, 1 });
	EXPECT_EQ(res.size(), 0);
	vectorContains(res, {});

	res = data.getCitiesInArea(Square{ {40, 40}, 20, 20 });
	EXPECT_EQ(res.size(), 1);
	vectorContains(res, { 8 });
}