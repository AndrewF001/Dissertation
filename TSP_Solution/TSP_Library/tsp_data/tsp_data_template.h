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

	using cityPTR = TSPType*;

public:
	const Square m_area;	// Size of the area	

	/// Constructors
	TspDataTemplate(const Square& size);
	TspDataTemplate(const Square& size, GenerationType type, std::mt19937& seed);
	TspDataTemplate(const Square& size, std::array<TSPType, Size> cities);
	~TspDataTemplate() = default;

	/// Getters Methods
	//const std::array<TSPType, Size>& getAllCities() const { return m_cities; };	// This is too much privalage
	//inline const TSPType& getCity(const cityID city) const { return m_cities[city]; };
	inline const Point2D& getCityPoint(const cityID city) const { return m_cities[city].getPoint(); };
	inline size_t getCityRoutePosition(const cityID city) const { return m_cities[city].getRoutePosition(); };
	inline const size_t getNumberOfCities() const {	return m_city_count; };
	std::vector<cityID> getCitiesInArea(const Square& s) const;
	double getDistance(cityID city1, cityID city2);
	double calcDeivation(const cityID new_city, const cityID old_city1, const cityID old_city2);	// Used by outside classes
	double getDistanceConst(cityID city1, cityID city2) const { return m_cities[city1].getDistance(m_cities[city2]); }; // Used by outside classes

	/// Route Methods
	const std::array<cityPTR, Size + 1>& getRoute() const { return m_route; };
	size_t getRouteSize() const { return m_route_count; };
	cityID getRouteCityID(const cityPTR position) const { return position - &m_cities[0]; };
	bool isCityInRoute(const cityID city) const { return m_cities[city].isInRoute(); };
	void setCityPos(const cityID city_id, const cityID pos);	// Used by construction algorithms to create a route
	void swapCitiesPos(const cityID city1, const cityID city2);	// Used by optimisation algorithms to improve a route

	/// Initalisation Methods
	void initaliseCache();
	void initalisePartition();

	/// Debugging Methods
	bool validRoute() const;

private:
	/// Members Data
	size_t m_city_count = 0;				// Live count of the number of cities
	std::array<TSPType, Size> m_cities;		// Array of cities

	size_t m_route_count = 0;				// Live count of the number of cities in the route
	std::array<cityPTR, Size + 1> m_route{};	// Array of the cities in the route
	//std::array<size_t, Size> m_city_pos{};	// Array of the positions of the cities in the tour
	
	
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
	std::vector<cityID> _noPartitioningGetCities(const Square& s) const;
	std::vector<cityID> _quadtreeGetCities(const Square& s) const;
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
TspDataTemplate<TSPType, Size, Caching, Partitioning>::TspDataTemplate(const Square& size) : m_area(size) {
	defineVariables();
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
TspDataTemplate<TSPType, Size, Caching, Partitioning>::TspDataTemplate(const Square& size, GenerationType type, std::mt19937& seed) : m_area(size) {
	for (size_t i = 0; i < Size; i++)
		generateRandomCities(type, seed);

	defineVariables();
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
TspDataTemplate<TSPType, Size, Caching, Partitioning>::TspDataTemplate(const Square& size, std::array<TSPType, Size> cities) : m_area(size), m_cities(cities), m_city_count(Size) {
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

	m_cities[m_city_count++] = TSPType(type, m_area, seed);
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<cityID> TspDataTemplate<TSPType, Size, Caching, Partitioning>::getCitiesInArea(const Square& s) const {
	if constexpr (Partitioning == PartitioningType::NoPartitioning)
		return _noPartitioningGetCities(s);
	if constexpr (Partitioning == PartitioningType::QuadTree)
		return _quadtreeGetCities(s);

	throw std::runtime_error("TspDataTemplate::getCities(), impossible to reach code reached!");
	return {};
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
double TspDataTemplate<TSPType, Size, Caching, Partitioning>::getDistance(cityID city1, cityID city2) {			// Not const as it modifies the cache for partial caching
	if constexpr (Caching == CachingType::Full)				// Caching is constexpr, so this is optimized out
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
}
template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
inline double TspDataTemplate<TSPType, Size, Caching, Partitioning>::calcDeivation(const cityID new_city, const cityID old_city1, const cityID old_city2) {
	return getDistance(new_city, old_city1) + getDistance(new_city, old_city2) - getDistance(old_city1, old_city2);
}
;

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::setCityPos(const cityID city, const size_t pos) {
#ifdef _DEBUG
	if (m_route_count >= Size)
		throw std::out_of_range("TSP_Data::setCityPos: The number of cities in the route exceeds the maximum size of the array.");
	if (pos > m_route_count)
		throw std::out_of_range("TSP_Data::setCityPos: The position is greater than the number of cities in the route.");
	if (city >= m_city_count)
		throw std::out_of_range("TSP_Data::setCityPos: The city is not in the array.");
	if (isCityInRoute(city))
		std::cout << "City: " << city << " added multiple times\n";	// TODO: Change to throw
#endif

	for (size_t i = pos; i < m_route_count; i++) {
		m_route[i]->incrementRoutePosition();
	}

	// Shift positions correctly without deleting the final element
	auto src = m_route.data() + pos;
	auto dest = src + 1;
	auto count = sizeof(cityPTR) * (m_route_count - pos + 1);
	memmove(dest, src, count);

	//for (size_t i = m_route_count + 1; i > pos; i--)	// TODO: Replace for more efficient method
	//	m_route[i] = m_route[i - 1];

	m_route_count++;
	m_route[pos] = &m_cities[city];
	if (pos == 0)
		m_route[m_route_count] = &m_cities[city];

	m_cities[city].setRoutePosition(pos);

#ifdef _DEBUG
	if (m_route[0] != m_route[m_route_count])
		throw std::runtime_error("TSP_Data::setCityPos: The first and last city in the route are not the same.");
#endif
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::swapCitiesPos(const cityID city1, const cityID city2) {
#ifdef _DEBUG
	if (city1 >= m_route_count || city2 >= m_route_count)
		throw std::out_of_range("TSP_Data::swapCitiesPos: The city is not in the route.");
#endif

	const cityID pos1 = m_cities[city1].m_route_position;
	const cityID pos2 = m_cities[city2].m_route_position;
	m_cities[city1].m_route_position = pos2;
	m_cities[city2].m_route_position = pos1;
	std::swap(m_route[pos1], m_route[pos2]);
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::initaliseCache() {
	if constexpr (Caching == CachingType::Full) {
		for (cityID i = 0; i < m_city_count; i++) {
			for (cityID j = i; j < m_city_count; j++) {		// Could do vectorization here
				m_cache[i][j] = m_cities[i].getDistance(m_cities[j]);
				m_cache[j][i] = m_cache[i][j];
			}
		}
	}
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::initalisePartition() {
	if constexpr (Partitioning == PartitioningType::NoPartitioning)
		return;
	if constexpr (Partitioning == PartitioningType::QuadTree)
		return _quadTreeInitalisePartition();

	//static_assert(false, "TspDataTemplate::initalisePartition(), impossible to reach code reached!");	// TODO: Odd behaviour, check later
	throw std::runtime_error("TspDataTemplate::initalisePartition(), impossible to reach code reached!");
};

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
inline bool TspDataTemplate<TSPType, Size, Caching, Partitioning>::validRoute() const {
	bool valid = true;

	// Check is cycle
	if (m_route[0] != m_route[Size]) {
		std::cout << "Route is not a cycle (End point doesn't equal Start point)\n";
		valid = false;
	}

	// Check route lenght
	if (m_route_count != Size) {
		std::cout << "Route is wrong length\n";
		valid = false;
	}

	// Check which points aren't visited
	for (size_t i = 0; i < Size; i++) {
		if (!isCityInRoute(i)) {
			std::cout << "Node " << i << " never visited!\n";
			valid = false;
		}
	}

	// Check if a point is visited twice
    std::array<bool, Size> map = {false};
	for (size_t i = 0; i < Size; i++) {
		if (map[getRouteCityID(m_route[i])]) {
			std::cout << "Node " << i << " visited twice!\n";
			valid = false;
			continue;
		}
		map[getRouteCityID(m_route[i])] = true;
	}

	return valid;
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::defineVariables() {
	for (auto& row : m_cache)
		std::fill_n(row.begin(), row.size(), DBL_MAX);	// Fills the cache with DBL_MAX, needed for Partial Caching

	for (cityID i = 0; i < Size; i++) {	// Fills the route with SIZE_MAX
		m_route[i] = nullptr;
	}
};

// TODO: Add 3D support
template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<cityID> TspDataTemplate<TSPType, Size, Caching, Partitioning>::_noPartitioningGetCities(const Square& s) const {
	std::vector<cityID> output;
	output.reserve(Size);

	for (cityID i = 0; i < getNumberOfCities(); i++) {
		auto& point = getCityPoint(i);
		if (point.x >= s.p.x && point.y >= s.p.y &&
			point.x <= s.p.x + s.width && point.y <= s.p.y + s.height)
			output.push_back(i);
	}

	return output;
}

// TODO: implement
template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::_quadTreeInitalisePartition() {}

// TODO: implement
template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<cityID> TspDataTemplate<TSPType, Size, Caching, Partitioning>::_quadtreeGetCities(const Square& s) const {
	std::vector<cityID> output;
	output.reserve(Size);

	return output;
}