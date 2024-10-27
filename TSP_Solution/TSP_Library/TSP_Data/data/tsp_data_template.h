#pragma once
#include <vector>
#include <random>
#include "tsp_constructs.h"

template <class TSPType, CachingType Caching, class Partitioning>
class TspDataTemplate {
	// Type checking
	//static_assert(std::is_base_of<Data_Base, TSPType>::value, "TSPType must be a derived class of TSPType in TSP_Data<T,C,P>");
	//static_assert(std::is_base_of<Partitioning_Base, Partitioning>::value, "Partitioning must be a derived class of Partitioning_Base in TSP_Data<T,C,P>");
public:	
	// Constructors
	TspDataTemplate() = default;
	~TspDataTemplate() = default;

	// Methods
	// Adders
	void addCity(const Point3D& city) {
		m_cities.emplace_back(m_cities.size(), city);
	};

	void generateRandomCities(GenerationType type, const Cube &size, std::mt19937 &seed) {
		m_cities.emplace_back(m_cities.size(), type, size, seed);
	};

	// Getters
	inline unsigned int const getNumberOfCities() const {
		return m_cities.size();
	};

	std::vector<TSPType> const& getAllCities() const {
		return m_cities;
	};

	std::vector<TSPType> getCities(const Cube& s) const {
		std::vector<T> output;
		output.reserve(m_cities.size());

		return output;
	};

	double getDistance(const TSPType &city1, const TSPType& city2) const {
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
	Cube m_size;
	std::vector<TSPType> m_cities;
	std::vector<std::vector<double>> m_cache;	// Only 8 bytes of stack memory
	Partitioning m_partition;
};


