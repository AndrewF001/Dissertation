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
	TspDataTemplate(const Square& size);
	TspDataTemplate(const Square& size, GenerationType type, std::mt19937& seed);
	TspDataTemplate(const Square& size, std::array<TSPType, Size> cities);
	~TspDataTemplate() = default;

	/// Getters Methods
	inline const size_t getNumberOfCities() const {	return m_city_count; };
	const std::array<TSPType, Size>& getAllCities() const {	return m_cities; };		//TODO: delete later
	std::vector<size_t> getCitiesInArea(const Square& s) const;
	double getDistance(size_t city1, size_t city2);
	double getDistanceConst(size_t city1, size_t city2) const { return m_cities[city1].getDistance(m_cities[city2]); }; // Used by outside classes

	/// Route Methods
	const std::array<size_t, Size>& getRoute() const { return m_route; };
	size_t getRouteSize() const { return m_city_count; };
	size_t getCityPos(const size_t index) const { return m_city_pos[index]; };
	size_t getRoutePos(const size_t pos) const { return m_route[pos]; };
	bool isCityInRoute(const size_t city) const { return m_city_pos[city] < m_route_count; };
	void setCityPos(const size_t index, const size_t pos);	// Used by construction algorithms to create a route
	void swapCitiesPos(const size_t city1, const size_t city2);	// Used by optimisation algorithms to improve a route

	/// Initalisation Methods
	void initaliseCache();
	void initalisePartition();

private:
	/// Members Data
	size_t m_city_count = 0;				// Live count of the number of cities
	Square m_size;							// Size of the area	
	std::array<TSPType, Size> m_cities;		// Array of cities

	size_t m_route_count = 0;				// Live count of the number of cities in the route
	std::array<size_t, Size> m_city_pos{};	// Array of the positions of the cities in the tour
	std::array<size_t, Size> m_route{};		// Array of the cities in the route
	
	
	std::conditional_t<Caching == CachingType::None, 
		std::array<std::array<double, 0>, 0>,
		std::array<std::array<double, Size>, Size>> m_cache;	// Cache for the distances between the cities

	/// Adders Methods
	void addCity(const Point2D& city);
	void generateRandomCities(GenerationType type, std::mt19937& seed);

	/// Constructor Helper Methods
	void defineVariables();

private:	/// Partitioning Monolithic Code
	struct EMPTYCLASS {};	// Empty class for the conditional_t to assign zero bytes of memory

	// Partitioning Data
	std::conditional_t<Partitioning == PartitioningType::QuadTree, int, EMPTYCLASS> m_quadtree;	// Data  TODO: change int to QuadTree
	
	// Partitioning Initalisation
	void _quadTreeInitalisePartition();

	// Partitioning Getters
	std::vector<size_t> _noPartitioningGetCities(const Square& s) const;
	std::vector<size_t> _quadtreeGetCities(const Square& s) const;
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
TspDataTemplate<TSPType, Size, Caching, Partitioning>::TspDataTemplate(const Square& size) : m_size(size) {
	defineVariables();
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
TspDataTemplate<TSPType, Size, Caching, Partitioning>::TspDataTemplate(const Square& size, GenerationType type, std::mt19937& seed) : m_size(size) {
	for (size_t i = 0; i < Size; i++)
		generateRandomCities(type, seed);

	defineVariables();
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
TspDataTemplate<TSPType, Size, Caching, Partitioning>::TspDataTemplate(const Square& size, std::array<TSPType, Size> cities) : m_size(size), m_cities(cities), m_city_count(Size) {
	defineVariables();
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::addCity(const Point2D& city) {
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
std::vector<size_t> TspDataTemplate<TSPType, Size, Caching, Partitioning>::getCitiesInArea(const Square& s) const {
	if constexpr (Partitioning == PartitioningType::NonePartitioning)
		return _noPartitioningGetCities(s);
	if constexpr (Partitioning == PartitioningType::QuadTree)
		return _quadtreeGetCities(s);

	throw std::runtime_error(false, "TspDataTemplate::getCities(), impossible to reach code reached!");
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
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::setCityPos(const size_t city, const size_t pos) {
#ifdef _DEBUG
	if (m_route_count >= Size)
		throw std::out_of_range("TSP_Data::setCityPos: The number of cities in the route exceeds the maximum size of the array.");
	if (pos > m_route_count)
		throw std::out_of_range("TSP_Data::setCityPos: The position is greater than the number of cities in the route.");
#endif

	// Increment all cities that are greater than the new position
	for (auto& city_pos : m_city_pos) {
		if (city_pos >= pos)
			city_pos++;
	}

	// Shift positions (Deletes the final element!)
	memcpy(m_route.data() + pos + 1, m_route.data() + pos, sizeof(size_t) * (m_route_count - pos));

	m_city_pos[city] = pos;
	m_route[pos] = city;

	m_route_count++;
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::swapCitiesPos(const size_t city1, const size_t city2) {
#ifdef _DEBUG
	if (city1 >= m_route_count || city2 >= m_route_count)
		throw std::out_of_range("TSP_Data::swapCitiesPos: The city is not in the route.");
#endif

	const size_t pos1 = m_city_pos[city1];
	const size_t pos2 = m_city_pos[city2];
	m_city_pos[city1] = pos2;
	m_city_pos[city2] = pos1;
	std::swap(m_route[pos1], m_route[pos2]);
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
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::defineVariables() {
	for (auto& row : m_cache)
		std::fill_n(row.begin(), row.size(), DBL_MAX);	// Fills the cache with DBL_MAX, needed for Partial Caching

	for (size_t i = 0; i < Size; i++) {	// Fills the route with SIZE_MAX
		m_route[i] = SIZE_MAX;
		m_city_pos[i] = SIZE_MAX - Size; // When setCityPos() is called all values greater are incremented, this stops overflow
	}
};

// TODO: Add 3D support
template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<size_t> TspDataTemplate<TSPType, Size, Caching, Partitioning>::_noPartitioningGetCities(const Square& s) const {
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
std::vector<size_t> TspDataTemplate<TSPType, Size, Caching, Partitioning>::_quadtreeGetCities(const Square& s) const {
	std::vector<size_t> output;
	output.reserve(Size);

	return output;
}