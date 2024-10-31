#pragma once
#include <vector>
#include "../tsp_constructs.h"

template <class TSPType, size_t Size>
class PartitioningBase {
public:
	PartitioningBase() = default;
	virtual ~PartitioningBase() = default;

	virtual void initalisePartition(std::array<TSPType, Size> const& Data) = 0;
	virtual std::vector<size_t> getCities(const Cube& s) const = 0;
};

