/*
#pragma once
#include <vector>
#include <memory>
#include "../types/type_base.h"
#include "../partitioning/partitioning_base.h"
#include "tsp_constructs.h"


class TspDataRealtime {
public:
	// Constructors
	TspDataRealtime() = default;
	~TspDataRealtime() = default;

	// Methods
	// Adders
	void addCity(const unsigned int i);
	//void addCities(const std::vector<std::unique_ptr<Data_Base>>& cities);
	// Getters
	inline unsigned const int getNumberOfCities() const;
	double getDistance(const TypeBase &city1, const TypeBase &city2);
	std::vector<std::unique_ptr<TypeBase>>const* getAllCities() const;			// TODO: RAW POINTES ARE BAD! Look into weak_ptr
	std::vector<std::unique_ptr<TypeBase>> getCities(const Cube &s) const;
	// Setters
	void generateRandomCities(const GenerationType type, const int num_cities, const int seed, Cube size);

private:
	// Members
	Cube m_size = {{0,0,0},0,0};
	std::vector<std::unique_ptr<TypeBase>> m_cities;
	std::vector<std::vector<double>> m_cache;	// Only 8 bytes of stack memory
	std::unique_ptr<PartitioningBase> m_partition;
	CachingType m_caching;

};
*/