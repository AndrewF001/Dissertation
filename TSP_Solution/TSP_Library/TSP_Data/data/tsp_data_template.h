#pragma once
#include <vector>
#include "../types/type_base.h"
#include "../partitioning/partitioning_base.h"
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
	void addCity(const TSPType& city);
	void addCities(const std::vector<TSPType> &cities);
	// Getters
	inline unsigned int const getNumberOfCities() const;
	std::vector<TSPType> const& getAllCities() const;
	std::vector<TSPType> getCities(const Square& s) const;
	double getDistance(const TSPType &city1, const TSPType& city2) const;
	// Setters
	void generateRandomCities(const GenerationType type, const int num_cities, const int seed, Square size);

private:
	// Members
	Square m_size;
	std::vector<TSPType> m_cities;
	std::vector<std::vector<double>> m_cache;	// Only 8 bytes of stack memory
	Partitioning m_partition;
};


