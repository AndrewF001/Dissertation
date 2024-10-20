#include "TSP_Data.h"
#include <vector>

template<class T, CachingType C, class P>
void TSP_Data<T, C, P>::AddCity(const T& city) {
	m_cities.push_back(city);
}

template<class T, CachingType C, class P>
void TSP_Data<T, C, P>::AddCities(const std::vector<T> &cities) {
	m_cities.insert(m_cities.end(), cities.begin(), cities.end());
}

template<class T, CachingType C, class P>
inline unsigned int const TSP_Data<T, C, P>::GetNumberOfCities() const {
	return m_cities.size();
}

template<class T, CachingType C, class P>
const std::vector<T>& TSP_Data<T, C, P>::GetAllCities() const {
	return m_cities;
}

template<class T, CachingType C, class P>
std::vector<T> TSP_Data<T, C, P>::GetCities(const square &s) const {
	std::vector<T> output;
	output.reserve(m_cities.size());

	return output;
}

template<class T, CachingType C, class P>
double TSP_Data<T, C, P>::GetDistance(const T& city1, const T& city2) const {
	if (C == CachingType::Full)						// C is constexpr, so this is optimized out
		return m_cache[city1.m_id][city2.m_id];
	 
	double result;									// Use the same memory later
	if (C == CachingType::Partial) {				
		result =  m_cache[city1.m_id][city2.m_id];
		if(result != DBL_MAX)						// Check if the value is already in the cache
			return result;
	}

	result = city1.getDistance(city2);				// Calculate the distance
	if(C == CachingType::Partial)					// Store the result in the cache
		m_cache[city1.m_id][city2.m_id] = result;

	return result;
}

template<class T, CachingType C, class P>
void TSP_Data<T, C, P>::GenerateRandomCities(const GenerationType type, const int num_cities, const int seed, square size) {

}
