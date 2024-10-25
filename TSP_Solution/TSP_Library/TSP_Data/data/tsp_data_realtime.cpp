/*
#include "tsp_data_realtime.h"


void TspDataRealtime::addCity(const unsigned int i) {
	//m_cities.push_back(std::make_unique<Data_Base>(city));
}


inline unsigned int const TspDataRealtime::getNumberOfCities() const {
	return m_cities.size();
}

std::vector<std::unique_ptr<TypeBase>> const* TspDataRealtime::getAllCities() const {
	return &m_cities;
}

std::vector<std::unique_ptr<TypeBase>> TspDataRealtime::getCities(const Cube &s) const {
	std::vector<std::unique_ptr<TypeBase>> output;
	output.reserve(m_cities.size());

	return output;
}

double TspDataRealtime::getDistance(const TypeBase &city1, const TypeBase &city2) {
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

void TspDataRealtime::generateRandomCities(const GenerationType type, const int num_cities, const int seed, Cube size) {

}
*/