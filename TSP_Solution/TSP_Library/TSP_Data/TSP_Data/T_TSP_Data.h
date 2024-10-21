#pragma once
#include <vector>
#include "../Data_Types/Data_Base.h"
#include "../Partitioning/Partitioning_Base.h"
#include "TSP_Types.h"

template <class TSPType, CachingType Caching, class Partitioning>
class T_TSP_Data {
	// Type checking
	//static_assert(std::is_base_of<Data_Base, TSPType>::value, "TSPType must be a derived class of TSPType in TSP_Data<T,C,P>");
	//static_assert(std::is_base_of<Partitioning_Base, Partitioning>::value, "Partitioning must be a derived class of Partitioning_Base in TSP_Data<T,C,P>");
public:	
	// Constructors
	T_TSP_Data() = default;
	~T_TSP_Data() = default;

	// Methods
	// Adders
	void AddCity(const TSPType& city);
	void AddCities(const std::vector<TSPType> &cities);
	// Getters
	inline unsigned int const GetNumberOfCities() const;
	std::vector<TSPType> const& GetAllCities() const;
	std::vector<TSPType> GetCities(const square& s) const;
	double GetDistance(const TSPType &city1, const TSPType& city2) const;
	// Setters
	void GenerateRandomCities(const GenerationType type, const int num_cities, const int seed, square size);

private:
	// Members
	square m_size;
	std::vector<TSPType> m_cities;
	std::vector<std::vector<double>> m_cache;	// Only 8 bytes of stack memory
	Partitioning m_partition;
};


