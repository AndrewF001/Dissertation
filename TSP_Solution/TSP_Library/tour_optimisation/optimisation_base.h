#pragma once
#include "../tsp_data/tsp_data_template.h"
#include "logger.h"

template<class TSPType, size_t Size, CachingType Caching, PartitioningType Partitioning>
class OptimisationBase {
public:
	OptimisationBase(const std::string&& name) : m_name(std::move(name)) {};
	virtual ~OptimisationBase() = default;

	void optimiseTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) {
		Logger::log(m_name + " tour optimisation\n", 1);
		_optimiseTour(data);
	};

private:
	const std::string m_name;
	virtual void _optimiseTour(TspDataTemplate<TSPType, Size, Caching, Partitioning>& data) = 0;
};