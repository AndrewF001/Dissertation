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
	/// Type checking
	static_assert(std::is_base_of<TypeBase, TSPType>::value, "TSPType must be a derived class of TSPType in TSP_Data<T,C,P>");

public:
	/// Constructors
	TspDataTemplate(const Cube& size);
	TspDataTemplate(const Cube& size, GenerationType type, std::mt19937& seed);
	TspDataTemplate(const Cube& size, std::array<TSPType, Size> cities);
	~TspDataTemplate() = default;

	/// Adders Methods
	void addCity(const Point3D& city);
	void generateRandomCities(GenerationType type, std::mt19937& seed);

	/// Getters Methods
	inline const size_t getNumberOfCities() const {	return m_city_count; };
	const std::array<TSPType, Size>& getAllCities() const {	return m_cities; };		//TODO: delete later
	std::vector<size_t> getCities(const Cube& s) const;
	double getDistance(size_t city1, size_t city2);

	/// Initalisation Methods
	void initaliseCache();
	void initalisePartition();

private:
	/// Members Data
	size_t m_city_count = 0;				// Live count of the number of cities
	Cube m_size;						// Size of the area	
	std::array<TSPType, Size> m_cities;	// Array of cities
	std::conditional_t<Caching == CachingType::None, 
		std::array<std::array<double, 0>, 0>,
		std::array<std::array<double, Size>, Size>> m_cache;	// Cache for the distances between the cities

	/// Base Class Methods
	void defineCache();

private:	/// Partitioning Monolithic Code
	struct EMPTYCLASS {};	// Empty class for the conditional_t to assign zero bytes of memory

	// Partitioning Data
	std::conditional_t<Partitioning == PartitioningType::QuadTree, int, EMPTYCLASS> m_quadtree;	// Data  TODO: change int to QuadTree
	
	// Partitioning Initalisation
	void _quadTreeInitalisePartition();

	// Partitioning Getters
	std::vector<size_t> _noPartitioningGetCities(const Cube& s) const;
	std::vector<size_t> _quadtreeGetCities(const Cube& s) const;
};

template <class T, size_t S, CachingType C, PartitioningType P>
TspDataTemplate<T, S, C, P>::TspDataTemplate(const Cube& size) : m_size(size) {
	defineCache();
};

template <class T, size_t S, CachingType C, PartitioningType P>
TspDataTemplate<T, S, C, P>::TspDataTemplate(const Cube& size, GenerationType type, std::mt19937& seed) : m_size(size) {
	for (size_t i = 0; i < Size; i++)
		generateRandomCities(type, seed);

	defineCache();
};

template <class T, size_t S, CachingType C, PartitioningType P>
TspDataTemplate<T, S, C, P>::TspDataTemplate(const Cube& size, std::array<T, S> cities) : m_size(size), m_cities(cities), m_city_count(Size) {
	defineCache();
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::addCity(const Point3D& city) {
	if (m_city_count >= Size)
		throw std::out_of_range("TSP_Data::addCity: The number of cities exceeds the maximum size of the array.");

	m_cities[m_city_count++] = TSPType(city);
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::generateRandomCities(GenerationType type, std::mt19937& seed) {
	if (m_city_count >= Size)
		throw std::out_of_range("TSP_Data::generateRandomCities: The number of cities exceeds the maximum size of the array.");

	m_cities[m_city_count++] = TSPType(type, m_size, seed);
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<size_t> TspDataTemplate<TSPType, Size, Caching, Partitioning>::getCities(const Cube& s) const {
	if constexpr (Partitioning == PartitioningType::NonePartitioning)
		return _noPartitioningGetCities(s);
	if constexpr (Partitioning == PartitioningType::QuadTree)
		return _quadtreeGetCities(s);

	//static_assert(false, "TspDataTemplate::getCities(), impossible to reach code reached!");
	//throw std::runtime_error(false, "TspDataTemplate::getCities(), impossible to reach code reached!");
	return {};
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
double TspDataTemplate<TSPType, Size, Caching, Partitioning>::getDistance(size_t city1, size_t city2) {			// Not const as it modifies the cache for partial caching
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

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::initaliseCache() {
	if constexpr (Caching == CachingType::FULL) {
		for (size_t i = 0; i < m_city_count; i++) {
			for (size_t j = i; j < m_city_count; j++) {		// Could do vectorization here
				m_cache[i][j] = m_cities[i].getDistance(m_cities[j]);
				m_cache[j][i] = m_cache[i][j];
			}
		}
	}
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::initalisePartition() {
	if constexpr (Partitioning == PartitioningType::NonePartitioning)
		return;
	if constexpr (Partitioning == PartitioningType::QuadTree)
		return _quadTreeInitalisePartition();

	//static_assert(false, "TspDataTemplate::initalisePartition(), impossible to reach code reached!");	// TODO: Odd behaviour, check later
	throw std::runtime_error("TspDataTemplate::initalisePartition(), impossible to reach code reached!");
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::defineCache() {
	for (auto& row : m_cache)
		std::fill_n(row.begin(), row.size(), DBL_MAX);	// Fills the cache with DBL_MAX, needed for Partial Caching
};

// TODO: Add 3D support
template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<size_t> TspDataTemplate<TSPType, Size, Caching, Partitioning>::_noPartitioningGetCities(const Cube& s) const {
	std::vector<size_t> output;
	output.reserve(Size);

	for (size_t i = 0; i < getNumberOfCities(); i++) {
		if (m_cities[i].m_point.x >= s.p.x && m_cities[i].m_point.y >= s.p.y &&
			m_cities[i].m_point.x <= s.p.x + s.width && m_cities[i].m_point.y <= s.p.y + s.height)
			output.push_back(i);
	}

	return output;
}

// TODO: implement
template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::_quadTreeInitalisePartition() {}

// TODO: implement
template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<size_t> TspDataTemplate<TSPType, Size, Caching, Partitioning>::_quadtreeGetCities(const Cube& s) const {
	std::vector<size_t> output;
	output.reserve(Size);

	return output;
}