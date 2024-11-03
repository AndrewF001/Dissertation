#pragma once
#include <array>
#include <random>
#include <algorithm>
#include "tsp_constructs.h"
#include "types/type_base.h"

/// <summary>
///  Monolithic class to store, manage and access the TSP data for many different types 
/// </summary>
/// <typeparam name="TSPType"></typeparam>
/// <typeparam name="Size"></typeparam>
/// <typeparam name="Caching"></typeparam>
/// <typeparam name="Partitioning"></typeparam>
template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class TspDataTemplate {
	// Type checking
	static_assert(std::is_base_of<TypeBase, TSPType>::value, "TSPType must be a derived class of TSPType in TSP_Data<T,C,P>");

public:
	// Constructors
	TspDataTemplate(const Cube& c) : m_size(c) {
		for (auto& row : m_cache)
			std::fill_n(row.begin(), row.size(), DBL_MAX);
	};
	~TspDataTemplate() = default;

	/// Adders Methods
	// Add a city to the list
	void addCity(const Point3D& city) {
		if (m_city_count >= Size)
			throw std::out_of_range("TSP_Data::addCity: The number of cities exceeds the maximum size of the array.");

		m_cities[m_city_count++] = TSPType(city);
	};

	// generate a random city based on the Generation Type
	void generateRandomCities(GenerationType type, std::mt19937& seed) {
		if (m_city_count >= Size)
			throw std::out_of_range("TSP_Data::generateRandomCities: The number of cities exceeds the maximum size of the array.");

		m_cities[m_city_count++] = TSPType(type, m_size, seed);
	};

	/// Getters Methods
	// Get the number of cities in the array, different from the size of the array
	inline size_t const getNumberOfCities() const {
		return m_city_count;
	};

	// Gets a reference to the array		TODO: delete later
	std::array<TSPType, Size> const& getAllCities() const {
		return m_cities;
	};

	// Get the cities in a specific area
	std::vector<size_t> getCities(const Cube& s) const {
		if constexpr (Partitioning == PartitioningType::NonePartitioning)
			return _noPartitioningGetCities(s);
		if constexpr (Partitioning == PartitioningType::QuadTree)
			return _quadtreeGetCities(s);

		//static_assert(false, "TspDataTemplate::getCities(), impossible to reach code reached!");
		//throw std::runtime_error(false, "TspDataTemplate::getCities(), impossible to reach code reached!");
		return {};
	};

	// Get the distance between two cities using the city index
	double getDistance(size_t city1, size_t city2) {			// Not const as it modifies the cache for partial caching
		if constexpr (Caching == CachingType::FULL)				// Caching is constexpr, so this is optimized out
			return m_cache[city1][city2];

		double result;									// Use the same memory later
		if constexpr (Caching == CachingType::Partial) {
			result = m_cache[city1][city2];
			if (result != DBL_MAX)						// Check if the value is already in the cache
				return result;
		}

		result = m_cities[city1].getDistance(m_cities[city2]);	// Calculate the distance
		if constexpr (Caching == CachingType::Partial)			// Store the result in the cache
			m_cache[city1][city2] = result;

		return result;
	};

	// Initalise the cache with the distances between all the cities for full caching
	void initaliseCache() {
		if constexpr (Caching == CachingType::FULL) {
			for (size_t i = 0; i < m_city_count; i++) {
				for (size_t j = i; j < m_city_count; j++) {		// Could do vectorization here
					m_cache[i][j] = m_cities[i].getDistance(m_cities[j]);
					m_cache[j][i] = m_cache[i][j];
				}
			}
		}
	};

	// Initalise the partitioning for the cities
	void initalisePartition() {
		if constexpr (Partitioning == PartitioningType::NonePartitioning)
			return;
		if constexpr (Partitioning == PartitioningType::QuadTree)
			return _quadTreeInitalisePartition();

		//static_assert(false, "TspDataTemplate::initalisePartition(), impossible to reach code reached!");	// TODO: Odd behaviour, check later
		throw std::runtime_error("TspDataTemplate::initalisePartition(), impossible to reach code reached!");
	};

private:
	// Members Data
	size_t m_city_count = 0;	// Live count of the number of cities
	Cube m_size;				// Size of the area	
	std::array<TSPType, Size> m_cities;	// Array of cities
	std::conditional_t<Caching == CachingType::None, std::array<std::array<double, 0>, 0>, std::array<std::array<double, Size>, Size>> m_cache;	// Cache for the distances between the cities

private:	// Partitioning Monolithic Code
	struct EMPTYCLASS {};	// Empty class for the conditional_t to assign zero bytes of memory

	// No Partitioning
	// Doesn't have any data or initialisation
	std::vector<size_t> _noPartitioningGetCities(const Cube& s) const {		// TODO: Add 3D support
		std::vector<size_t> output;
		output.reserve(Size);

		for (size_t i = 0; i < getNumberOfCities(); i++) {
			if (m_cities[i].m_point.x >= s.p.x && m_cities[i].m_point.y >= s.p.y &&
				m_cities[i].m_point.x <= s.p.x + s.width && m_cities[i].m_point.y <= s.p.y + s.height)
				output.push_back(i);
		}

		return output;
	}

	// QuadTree Partitioning
	std::conditional_t<Partitioning == PartitioningType::QuadTree, int, EMPTYCLASS> m_quadtree;	// Data  TODO: change int to QuadTree
	
	void _quadTreeInitalisePartition() {	// Initialisation
		//m_quadtree = QuadTree<TSPType, Size>(m_cities, m_size);
	}

	std::vector<size_t> _quadtreeGetCities(const Cube& s) const { // Getter
		std::vector<size_t> output;
		output.reserve(Size);

		return output;
	}

};
