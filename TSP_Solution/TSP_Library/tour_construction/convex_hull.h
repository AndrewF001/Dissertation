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
		cityID north, east, south, west;
	};

	static MaxPoints maxPoints(TspDataTemplate<TSPType, Size, Caching, Partitioning> const& data) {
		MaxPoints output{};
		double max_x = DBL_MIN, max_y = DBL_MIN, min_x = DBL_MAX, min_y = DBL_MAX;
		for (cityID i = 0; i < Size; i++) {
			auto& city = data.getCityPoint(i);
			// Most North Point
			if (city.m_y > max_y) {
				max_y = city.m_y;
				output.north = i;
			}
			// Most South Point
			if (city.m_y < min_y) {
				min_y = city.m_y;
				output.south = i;
			}
			// Most East Point
			if (city.m_x > max_x) {
				max_x = city.m_x;
				output.east = i;
			}
			// Most West Point
			if (city.m_x < min_x) {
				min_x = city.m_x;
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
	static std::vector<cityID> convexHullQuatar(TspDataTemplate<TSPType, Size, Caching, Partitioning> const& data, cityID new_point, const cityID dest) {
		std::vector<cityID> output;
		cityID last_point = new_point;
		do {
			// setup for new iteration
			output.push_back(new_point);
			last_point = new_point;
			auto& last_city = data.getCityPoint(last_point);
			double grad = ConvexHull::gradent_set<gradent>();
			const auto& search = data.getCitiesInArea(last_point, dest);
			// find best fit
			for (const auto& city : search) {	// TODO: Only find cities in correct quater
				auto& new_city = data.getCityPoint(city);
				double g = last_city.gradient(new_city);
				if (gradent && g > grad) {
					grad = g;
					new_point = city;
				}
				else if (!gradent && g < grad) {
					grad = g;
					new_point = city;
				}
			} 
			// Check if a new best fit was found
		} while (new_point != dest);

		return output;
	};

	template<bool left, bool gradent>
	static std::vector<cityID> convexHullHalf(TspDataTemplate<TSPType, Size, Caching, Partitioning> const& data, cityID new_point) {
		std::vector<cityID> output;
		cityID last_point = new_point;
		do {
			// setup for new iteration
			output.push_back(new_point);
			last_point = new_point;
			auto& last_city = data.getCityPoint(last_point);
			double grad = ConvexHull::gradent_set<gradent>();

			// find best fit
			for (cityID i = 0; i < Size; i++) {	// TODO: Only find cities in correct quater
				auto& new_city = data.getCityPoint(i);
				if (ConvexHull::left_statement<left>(last_city.m_x, new_city.m_x))
					continue;

				double g = last_city.gradient(new_city);
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

		std::vector<cityID> upper_left = ConvexHull::convexHullQuatar<false, true>(data, points.west, points.north);
		std::vector<cityID> upper_right = ConvexHull::convexHullQuatar<false, false>(data, points.north, points.east);
		std::vector<cityID> lower_right = ConvexHull::convexHullQuatar<true, false>(data, points.east, points.south);
		std::vector<cityID> lower_left = ConvexHull::convexHullQuatar<true, true>(data, points.south, points.west);

		size_t idx = 0;
		for (const auto city : upper_left)
			data.setCityPos(city, idx++);
		for (const auto city : upper_right)
			data.setCityPos(city, idx++);
		for (const auto city : lower_right)
			data.setCityPos(city, idx++);
		for (const auto city : lower_left)
			data.setCityPos(city, idx++);


		//std::vector<cityID> upper = ConvexHull::convexHullHalf<false, true>(data, points.west);
		//for (size_t i = 0; i < upper.size(); i++){
		//	data.setCityPos(upper[i], i);
		//}
		//
		//std::vector<cityID> lower = ConvexHull::convexHullHalf<true, true>(data, upper.back());
		//for (size_t i = 1; i < lower.size() - 1; i++) {
		//	data.setCityPos(lower[i], i + upper.size() - 1);
		//}
	};
};

