#pragma once
#include <array>
#include <random>
#include <algorithm>
#include "tsp_constructs.h"
#include "types/type_base.h"
//#include "partitioning/partitioning_base.h"

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class TspDataTemplate {
	// Type checking
	static_assert(std::is_base_of<TypeBase, TSPType>::value, "TSPType must be a derived class of TSPType in TSP_Data<T,C,P>");
	//static_assert(std::is_base_of<PartitioningBase<TSPType, Size>, Partitioning>::value, "Partitioning must be a derived class of Partitioning_Base in TSP_Data<T,C,P>");
public:
	// Constructors
	TspDataTemplate(const Cube& c) : m_size(c) {
		for (auto& row : m_cache) {
			std::fill_n(row.begin(), row.size(), DBL_MAX);
		}
	};
	~TspDataTemplate() = default;

	// Methods
	// Adders
	void addCity(const Point3D& city) {
		if (m_city_count >= Size)
			throw std::out_of_range("TSP_Data::addCity: The number of cities exceeds the maximum size of the array.");
		m_cities[m_city_count++] = TSPType(city);
	};

	void generateRandomCities(GenerationType type, const Cube& size, std::mt19937& seed) {
		if (m_city_count >= Size)
			throw std::out_of_range("TSP_Data::generateRandomCities: The number of cities exceeds the maximum size of the array.");
		m_cities[m_city_count++] = TSPType(type, size, seed);
	};

	// Getters
	inline size_t const getNumberOfCities() const {
		return m_city_count;
	};

	std::array<TSPType, Size> const& getAllCities() const {
		return m_cities;
	};

	std::vector<size_t> getCities(const Cube& s) const {
		if (Partitioning == PartitioningType::None){}
			//throw std::runtime_error("TspDataTemplate::getCities: Partitioning is not implemented.");
		return m_partition.getCities(s);
	};

	double getDistance(size_t city1, size_t city2) {
		if (Caching == CachingType::FULL)				// Caching is constexpr, so this is optimized out
			return m_cache[city1][city2];

		double result;									// Use the same memory later
		if (Caching == CachingType::Partial) {
			result = m_cache[city1][city2];
			if (result != DBL_MAX)						// Check if the value is already in the cache
				return result;
		}

		result = m_cities[city1].getDistance(m_cities[city2]);	// Calculate the distance
		if (Caching == CachingType::Partial)			// Store the result in the cache
			m_cache[city1][city2] = result;

		return result;
	};

	void initaliseCache() {
		if (Caching == CachingType::FULL) {
			for (size_t i = 0; i < m_city_count; i++) {
				for (size_t j = i; j < m_city_count; j++) {		// Could do vectorization here
					m_cache[i][j] = m_cities[i].getDistance(m_cities[j]);
					m_cache[j][i] = m_cache[i][j];
				}
			}
		}
	};

	void initalisePartition() {
		if (Partitioning == PartitioningType::NonePartitioning){}
			//throw std::runtime_error("TspDataTemplate::initalisePartition: Partitioning is not implemented.");
	};

private:
	// Members
	size_t m_city_count = 0;
	Cube m_size;
	std::array<TSPType, Size> m_cities;
    std::conditional_t<Caching == CachingType::None, std::array<std::array<double, 0>, 0>, std::array<std::array<double, Size>, Size>> m_cache;
};
