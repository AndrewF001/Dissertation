#pragma once
#include <vector>
#include <memory>
#include "../types/type_base.h"
#include "../partitioning/partitioning_base.h"
#include "tsp_constructs.h"

namespace runtime {
	class TspDataRealtime {
	public:
		// Constructors
		TspDataRealtime() = default;
		~TspDataRealtime() = default;

		// Methods
		// Adders
		void AddCity(const unsigned int i);
		//void AddCities(const std::vector<std::unique_ptr<Data_Base>>& cities);
		// Getters
		inline unsigned int const GetNumberOfCities() const;
		double GetDistance(const TypeBase &city1, const TypeBase &city2);
		std::vector<std::unique_ptr<TypeBase>> const &GetAllCities() const;
		std::vector<std::unique_ptr<TypeBase>> GetCities(const Square &s) const;
		// Setters
		void GenerateRandomCities(const GenerationType type, const int num_cities, const int seed, Square size);

	private:
		// Members
		Square m_size = {{0,0},0,0};
		std::vector<std::unique_ptr<TypeBase>> m_cities;
		std::vector<std::vector<double>> m_cache;	// Only 8 bytes of stack memory
		std::unique_ptr<PartitioningBase> m_partition;
		CachingType m_caching;

	};
}
