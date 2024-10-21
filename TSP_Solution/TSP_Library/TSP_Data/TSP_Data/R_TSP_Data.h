#pragma once
#include <vector>
#include <memory>
#include "../Data_Types/Data_Base.h"
#include "../Partitioning/Partitioning_Base.h"
#include "TSP_Types.h"

namespace runtime {
	class R_TSP_Data {
	public:
		// Constructors
		R_TSP_Data() = default;
		~R_TSP_Data() = default;

		// Methods
		// Adders
		void AddCity(const unsigned int i);
		//void AddCities(const std::vector<std::unique_ptr<Data_Base>>& cities);
		// Getters
		inline unsigned int const GetNumberOfCities() const;
		double GetDistance(const Data_Base &city1, const Data_Base &city2);
		std::vector<std::unique_ptr<Data_Base>> const &GetAllCities() const;
		std::vector<std::unique_ptr<Data_Base>> GetCities(const square &s) const;
		// Setters
		void GenerateRandomCities(const GenerationType type, const int num_cities, const int seed, square size);

	private:
		// Members
		square m_size;
		std::vector<std::unique_ptr<Data_Base>> m_cities;
		std::vector<std::vector<double>> m_cache;	// Only 8 bytes of stack memory
		std::unique_ptr<Partitioning_Base> m_partition;
		CachingType m_caching;

	};
}
