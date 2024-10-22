#include <vector>
#include "tsp_data_template.h"

// !! No clue why renaming the template variable names causes a linker error !!
template<class TSPType, CachingType Caching, class Partitioning>
void TspDataTemplate<TSPType, Caching, Partitioning>::addCity(const TSPType &city) {
	m_cities.push_back(city);
}

template<class T, CachingType C, class P>
void TspDataTemplate<T, C, P>::addCities(const std::vector<T> &cities) {
	m_cities.insert(m_cities.end(), cities.begin(), cities.end());
}

template<class T, CachingType C, class P>
inline unsigned int const TspDataTemplate<T, C, P>::getNumberOfCities() const {
	return m_cities.size();
}

template<class T, CachingType C, class P>
const std::vector<T>&TspDataTemplate<T, C, P>::getAllCities() const {
	return m_cities;
}

template<class T, CachingType C, class P>
std::vector<T> TspDataTemplate<T, C, P>::getCities(const Square &s) const {
	std::vector<T> output;
	output.reserve(m_cities.size());

	return output;
}

// !! No clue why renaming the template variable names causes a linker error !!
template<class TSPType, CachingType Caching, class Partitioning>
double TspDataTemplate<TSPType, Caching, Partitioning>::getDistance(const TSPType &city1, const TSPType &city2) const {
	if(Caching == CachingType::Full)						// C is constexpr, so this is optimized out
		return m_cache[city1.m_id][city2.m_id];

	double result;									// Use the same memory later
	if(Caching == CachingType::Partial) {
		result = m_cache[city1.m_id][city2.m_id];
		if(result != DBL_MAX)						// Check if the value is already in the cache
			return result;
	}

	result = city1.getDistance(city2);				// Calculate the distance
	if(Caching == CachingType::Partial)					// Store the result in the cache
		m_cache[city1.m_id][city2.m_id] = result;

	return result;
}

template<class T, CachingType C, class P>
void TspDataTemplate<T, C, P>::generateRandomCities(const GenerationType type, const int num_cities, const int seed, Square size) {

}
