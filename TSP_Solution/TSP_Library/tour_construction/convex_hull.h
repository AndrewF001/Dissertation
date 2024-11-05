#pragma once
#include "../tsp_data/tsp_data_template.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class ConvexHull
{
public:
	ConvexHull() {};
	~ConvexHull() {};

	static void runSingle(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) {
		static_assert(Size >= 3, "Convex Hull requires at least 3 cities");

		ConvexHull::convexHullFull(data);
	};

	static void runMulti(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) {
		static_assert(Size >= 3, "Convex Hull requires at least 3 cities");
	};

private:
	struct MaxPoints {
		size_t north, east, south, west;
	};

	static MaxPoints maxPoints(TspDataTemplate<TSPType, Size, Caching, Partitioning> const& data) {
		MaxPoints output{};
		double max_x = DBL_MIN, max_y = DBL_MIN, min_x = DBL_MAX, min_y = DBL_MAX;
		auto cities = data.getAllCities();
		for (size_t i = 0; i < Size; i++) {
			// Most North Point
			if (cities[i].m_point.y > max_y) {
				max_y = cities[i].m_point.y;
				output.north = i;
			}
			// Most South Point
			if (cities[i].m_point.y < min_y) {
				min_y = cities[i].m_point.y;
				output.south = i;
			}
			// Most East Point
			if (cities[i].m_point.x > max_x) {
				max_x = cities[i].m_point.x;
				output.east = i;
			}
			// Most West Point
			if (cities[i].m_point.x < min_x) {
				min_x = cities[i].m_point.x;
				output.west = i;
			}
		}
		return output;
	};

	// Check if the point is to the left or right of the line
	template<bool left_direction>
	static inline bool left_statement(double x1, double x2) {
		if (left_direction) {
			return x2 > x1;
		}
		else {
			return x1 > x2;
		}
	};

	// Reset function for gradiant variable
	template<bool positive_gradent>
	static inline double gradent_set() {
		if (positive_gradent) {
			return -DBL_MAX;
		}
		else {
			return DBL_MAX;
		}
	};

	template<bool left, bool gradent>
	static std::vector<size_t> convexHullHalf(TspDataTemplate<TSPType, Size, Caching, Partitioning> const& data, size_t start) {
		std::vector<size_t> output;
		size_t last_point;
		size_t new_point = start;
		double grad;
		do {
			// setup for new iteration
			last_point = new_point;
			output.push_back(last_point);
			grad = ConvexHull::gradent_set<gradent>();

			// find best fit
			auto cities = data.getAllCities();
			for (size_t i = 0; i < Size; i++) {	// TODO: Only find cities in correct quater
				if (ConvexHull::left_statement<left>( cities[last_point].m_point.x, cities[i].m_point.x))
					continue;

				double g = cities[last_point].m_point.gradient(cities[i].m_point);
				if (gradent && g > grad) {
					grad = g;
					new_point = i;
				}
				else if (!gradent && g < grad) {
					grad = g;
					new_point = i;
				}

			}
			// Check if a new best fit was found
		} while (last_point != new_point);

		return output;
	};

	static void convexHullFull(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) {
		MaxPoints points = ConvexHull::maxPoints(data);
		std::cout << "North: " << points.north << " East: " << points.east << " South: " << points.south << " West: " << points.west << "\n";

		std::vector<size_t> upper = ConvexHull::convexHullHalf<false, true>(data, points.west);
		for (size_t i = 0; i < upper.size(); i++){
			data.setCityPos(upper[i], i);
		}
		
		std::vector<size_t> lower = ConvexHull::convexHullHalf<true, true>(data, upper.back());
		for (size_t i = 1; i < lower.size() - 1; i++) {
			data.setCityPos(lower[i], i + upper.size() - 1);
		}
	};
};

