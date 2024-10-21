#include "R_TSP_Data.h"

namespace runtime {
	void R_TSP_Data::AddCity(const unsigned int i) {
		//m_cities.push_back(std::make_unique<Data_Base>(city));
	}

	/*
	void R_TSP_Data::AddCities(const std::vector<std::unique_ptr<Data_Base>> &cities) {
		//m_cities.insert(m_cities.end(), cities.begin(), cities.end());
	}*/

	inline unsigned int const R_TSP_Data::GetNumberOfCities() const {
		return m_cities.size();
	}

	const std::vector<std::unique_ptr<Data_Base>> &R_TSP_Data::GetAllCities() const {
		//return m_cities;
	}

	std::vector<std::unique_ptr<Data_Base>> R_TSP_Data::GetCities(const square &s) const {
		std::vector<std::unique_ptr<Data_Base>> output;
		output.reserve(m_cities.size());

		return output;
	}

	double R_TSP_Data::GetDistance(const Data_Base &city1, const Data_Base &city2) {
		if(m_caching == CachingType::Full)						// m_caching is constexpr, so this is optimized out
			return m_cache[city1.m_id][city2.m_id];

		double result;									// Use the same memory later
		if(m_caching == CachingType::Partial) {
			result = m_cache[city1.m_id][city2.m_id];
			if(result != DBL_MAX)						// Check if the value is already in the cache
				return result;
		}

		result = city1.getDistance(city2);				// Calculate the distance
		if(m_caching == CachingType::Partial)					// Store the result in the cache
			m_cache[city1.m_id][city2.m_id] = result;

		return result;
	}

	void R_TSP_Data::GenerateRandomCities(const GenerationType type, const int num_cities, const int seed, square size) {

	}
}