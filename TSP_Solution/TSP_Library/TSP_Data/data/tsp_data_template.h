#pragma once
#include <array>
#include <random>
#include "tsp_constructs.h"
#include "types/type_base.h"
template <class TSPType, CachingType Caching, class Partitioning, size_t Size>
class TspDataTemplate {
	// Type checking
	static_assert(std::is_base_of<TypeBase, TSPType>::value, "TSPType must be a derived class of TSPType in TSP_Data<T,C,P>");
	//static_assert(std::is_base_of<Partitioning_Base, Partitioning>::value, "Partitioning must be a derived class of Partitioning_Base in TSP_Data<T,C,P>");
public:
	// Constructors
	TspDataTemplate(const Cube& c) : m_size(c) {};
	~TspDataTemplate() = default;

	// Methods
	// Adders
	void addCity(const Point3D& city) {
		if (m_city_count >= Size)
			throw std::out_of_range("TSP_Data::addCity: The number of cities exceeds the maximum size of the array.");
		m_cities[m_city_count++] = TSPType(m_city_count, city);
	};

	void generateRandomCities(GenerationType type, const Cube& size, std::mt19937& seed) {
		if (m_city_count >= Size)
			throw std::out_of_range("TSP_Data::generateRandomCities: The number of cities exceeds the maximum size of the array.");
		m_cities[m_city_count++] = TSPType(m_city_count, type, size, seed);
	};

	// Getters
	inline size_t const getNumberOfCities() const {
		return m_city_count;
	};

	std::array<TSPType, Size> const& getAllCities() const {
		return m_cities;
	};

	std::vector<size_t> getCities(const Cube& s) const {
		std::vector<size_t> output;
		output.reserve(m_cities.size());

		return output;
	};

	double getDistance(const TSPType& city1, const TSPType& city2) const {
		if (Caching == CachingType::Full)						// C is constexpr, so this is optimized out
			return m_cache[city1.m_id][city2.m_id];

		double result;									// Use the same memory later
		if (Caching == CachingType::Partial) {
			result = m_cache[city1.m_id][city2.m_id];
			if (result != DBL_MAX)						// Check if the value is already in the cache
				return result;
		}

		result = city1.getDistance(city2);				// Calculate the distance
		if (Caching == CachingType::Partial)					// Store the result in the cache
			m_cache[city1.m_id][city2.m_id] = result;

		return result;
	};

private:
	// Members
	size_t m_city_count = 0;
	Cube m_size;
	std::array<TSPType, Size> m_cities;
	std::array<std::array<double, Size>, Size> m_cache;
	Partitioning m_partition;
};


