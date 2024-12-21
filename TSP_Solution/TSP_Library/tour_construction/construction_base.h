#pragma once
#include "../tsp_data/tsp_data_template.h"
#include "logger.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class ConstructionBase {
public:
	ConstructionBase(const std::string&& name) : m_name(std::move(name)) {};
	virtual ~ConstructionBase() = default;

	void constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& m_data_ref) {
		Logger::log(m_name + " tour construction\n", 1);
		_constructTour(m_data_ref);
	};

private:
	const std::string m_name;
	virtual void _constructTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& m_data_ref) = 0;
};
