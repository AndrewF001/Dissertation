#pragma once
#include <array>
#include <random>
#include <algorithm>

#include "tsp_constructs.h"
#include "types/type_base.h"
#include "partitioning/quadtree.h"

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
	TspDataTemplate(const Square& size, std::array<TSPType, Size>& cities);
	~TspDataTemplate() = default;

	/// Static Creation Methods
	static std::array<TSPType, Size> generateCities(const Square& size, GenerationType type, std::mt19937& seed);
	static TSPType generateRandomCities(const Square& size, GenerationType type, std::mt19937& seed);

	/// Getters Methods
	//const std::array<TSPType, Size>& getAllCities() const { return m_cities; };	// This is too much privalage
	//inline const TSPType& getCity(const cityID city) const { return m_cities[city]; };
	inline const Point2D& getCityPoint(const cityID city) const { return m_cities[city].getPoint(); };
	inline const cityID getCityRoutePosition(const cityID city) const { return m_cities[city].getRoutePosition(); };
	inline const size_t getNumberOfCities() const {	return m_city_count; };
	std::vector<cityID> getCitiesInArea(const Square& s) const;
	double getDistance(cityID city1, cityID city2);
	double calcDeivation(const cityID new_city, const cityID old_city1, const cityID old_city2);	// Used by outside classes
	double getDistanceConst(cityID city1, cityID city2) const { return m_cities[city1].getDistance(m_cities[city2]); }; // Used by outside classes

	/// Route Methods
	const std::array<cityPTR, Size + 1>& getRoute() const { return m_route; };
	size_t getRouteSize() const { return m_route_count; };
	double getRouteLength() const;
	cityID getRouteCityID(const cityPTR position) const { return position - &m_cities[0]; };
	bool isCityInRoute(const cityID city) const { return m_cities[city].isInRoute(); };
	void setCityPos(const cityID city_id, const cityID pos);	// Used by construction algorithms to create a route
	void swapRoutePos(const cityID city1, const cityID city2);	// Used by optimisation algorithms to improve a route

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
	
	
	std::conditional_t<Caching == CachingType::none, 
		std::array<std::array<double, 0>, 0>,
		std::array<std::array<double, Size>, Size>> m_cache;	// Cache for the distances between the cities

	/// Adders Methods
	void addCity(const Point2D& city);

private:	/// Partitioning Monolithic Code
	struct EMPTYCLASS {};	// Empty class for the conditional_t to assign zero bytes of memory

	// Partitioning Data
	std::conditional_t<Partitioning == PartitioningType::quadTree, std::unique_ptr<QuadTree>, EMPTYCLASS> m_quadtree;
	
	// Partitioning Initalisation
	void _quadTreeInitalisePartition();

	// Partitioning Getters
	std::vector<cityID> _noPartitioningGetCities(const Square& s) const;
	std::vector<cityID> _linearSearch(const Square& s) const;
	std::vector<cityID> _quadtreeGetCities(const Square& s) const;
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
TspDataTemplate<TSPType, Size, Caching, Partitioning>::TspDataTemplate(const Square& size) : m_area(size) {
	for (auto& row : m_cache)
		std::fill_n(row.begin(), row.size(), DBL_MAX);	// Fills the cache with DBL_MAX, needed for Partial Caching

	std::fill(m_route.begin(), m_route.end(), nullptr);	// Fills the route with nullptr
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
TspDataTemplate<TSPType, Size, Caching, Partitioning>::TspDataTemplate(const Square& size, GenerationType type, std::mt19937& seed) : TspDataTemplate(size) {
	m_cities = generateCities(size, type, seed);
	m_city_count = Size;
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
TspDataTemplate<TSPType, Size, Caching, Partitioning>::TspDataTemplate(const Square& size, std::array<TSPType, Size>& cities) : TspDataTemplate(size), m_cities(cities), m_city_count(Size) {};

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
inline std::array<TSPType, Size> TspDataTemplate<TSPType, Size, Caching, Partitioning>::generateCities(const Square& size, GenerationType type, std::mt19937& seed) {
	std::array<TSPType, Size> cities;

	for (size_t i = 0; i < Size; i++)
		cities[i] = generateRandomCities(size, type, seed);

	return cities;
}
template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
inline TSPType TspDataTemplate<TSPType, Size, Caching, Partitioning>::generateRandomCities(const Square& size, GenerationType type, std::mt19937& seed) {
	return TSPType(type, size, seed);
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::addCity(const Point2D& city) {
	if (m_city_count >= Size)
		throw std::out_of_range("TSP_Data::addCity: The number of cities exceeds the maximum size of the array.");

	m_cities[m_city_count++] = TSPType(city);
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<cityID> TspDataTemplate<TSPType, Size, Caching, Partitioning>::getCitiesInArea(const Square& s) const {
	if constexpr (Partitioning == PartitioningType::noPartitioning)
		return _noPartitioningGetCities(s);
	if constexpr (Partitioning == PartitioningType::quadTree)
		return _quadtreeGetCities(s);

	throw std::runtime_error("TspDataTemplate::getCities(), impossible to reach code reached!");
	return {};
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
double TspDataTemplate<TSPType, Size, Caching, Partitioning>::getDistance(cityID city1, cityID city2) {			// Not const as it modifies the cache for partial caching
	if constexpr (Caching == CachingType::full)				// Caching is constexpr, so this is optimized out
		return m_cache[city1][city2];

	double result;									// Use the same memory later
	if constexpr (Caching == CachingType::partial) {
		result = m_cache[city1][city2];
		if (result != DBL_MAX)						// Check if the value is already in the cache
			return result;
	}

	result = m_cities[city1].getDistance(m_cities[city2]);	// Calculate the distance
	if constexpr (Caching == CachingType::partial)			// Store the result in the cache
		m_cache[city1][city2] = result;

	return result;
};

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
inline double TspDataTemplate<TSPType, Size, Caching, Partitioning>::calcDeivation(const cityID new_city, const cityID old_city1, const cityID old_city2) {
	return getDistance(new_city, old_city1) + getDistance(new_city, old_city2) - getDistance(old_city1, old_city2);
};

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
inline double TspDataTemplate<TSPType, Size, Caching, Partitioning>::getRouteLength() const {
	double distance = 0;

	for (size_t i = 0; i < getRouteSize(); i++)
		distance += getDistanceConst(getRouteCityID(m_route[i]), getRouteCityID(m_route[i + 1]));

	return distance;
};

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
inline void TspDataTemplate<TSPType, Size, Caching, Partitioning>::setCityPos(const cityID city_id, const cityID pos) {
#ifdef _DEBUG
	if (m_route_count >= Size)
		throw std::out_of_range("TSP_Data::setCityPos: The number of cities in the route exceeds the maximum size of the array.");
	if (pos > m_route_count)
		throw std::out_of_range("TSP_Data::setCityPos: The position is greater than the number of cities in the route.");
	if (city_id >= m_city_count)
		throw std::out_of_range("TSP_Data::setCityPos: The city is not in the array.");
	if (isCityInRoute(city_id))
		std::cout << "City: " << city_id << " added multiple times\n";	// TODO: Change to throw
#endif

	for (size_t i = pos; i < m_route_count; i++) {
		m_route[i]->incrementRoutePosition();
	}

	// Shift positions correctly without deleting the final element
	auto src = m_route.data() + pos;
	auto dest = src + 1;
	auto count = sizeof(cityPTR) * (m_route_count - pos + 1);
	memmove(dest, src, count);

	m_route_count++;
	m_route[pos] = &m_cities[city_id];
	if (pos == 0)
		m_route[m_route_count] = &m_cities[city_id];

	m_cities[city_id].setRoutePosition(pos);

#ifdef _DEBUG
	if (m_route[0] != m_route[m_route_count])
		throw std::runtime_error("TSP_Data::setCityPos: The first and last city in the route are not the same.");
#endif
}

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::swapRoutePos(cityID route1, cityID route2) {
#ifdef _DEBUG
	if (route1 >= m_route_count || route2 >= m_route_count)
		throw std::out_of_range("TSP_Data::swapCitiesPos: The city is not in the route.");
	if (route1 >= route2)
		throw std::out_of_range("TSP_Data::swapCitiesPos: The first city must be before the second city.");
#endif

	route1 += 1;
	while (route1 < route2) {
		cityID city1 = getRouteCityID(m_route[route1]);
		cityID city2 = getRouteCityID(m_route[route2]);
		m_cities[city1].setRoutePosition(route2);
		m_cities[city2].setRoutePosition(route1);
		std::swap(m_route[route1], m_route[route2]);
		route1++;
		route2--;
	}
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::initaliseCache() {
	if constexpr (Caching == CachingType::full) {
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
	if constexpr (Partitioning == PartitioningType::noPartitioning)
		return;
	if constexpr (Partitioning == PartitioningType::quadTree)
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

// TODO: Add 3D support
template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<cityID> TspDataTemplate<TSPType, Size, Caching, Partitioning>::_noPartitioningGetCities(const Square& s) const {
	std::vector<cityID> output;
	output.reserve(Size);

	for (size_t i = 0; i < getNumberOfCities(); i++) {
		output.push_back(i);
	}

	return output;
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<cityID> TspDataTemplate<TSPType, Size, Caching, Partitioning>::_linearSearch(const Square& s) const {
	std::vector<cityID> output;
	output.reserve(Size);

	for (cityID i = 0; i < getNumberOfCities(); i++) {
		if (s.contains(getCityPoint(i)))
			output.push_back(i);
	}

	return output;
};

template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
void TspDataTemplate<TSPType, Size, Caching, Partitioning>::_quadTreeInitalisePartition() {
	m_quadtree = std::make_unique<QuadTree>(m_area);
	for (cityID i = 0; i < getNumberOfCities(); i++) {
		m_quadtree->insert(i, getCityPoint(i));
	}
};

// TODO: implement
template <class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
std::vector<cityID> TspDataTemplate<TSPType, Size, Caching, Partitioning>::_quadtreeGetCities(const Square& s) const {
	return m_quadtree->contains(s);
};