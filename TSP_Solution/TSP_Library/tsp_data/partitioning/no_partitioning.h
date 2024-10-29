#pragma once
#include "partitioning_base.h"

template <class TSPType, size_t Size>
class NoPartitioning : public PartitioningBase<TSPType, Size> {
public:
	NoPartitioning() = default;
	~NoPartitioning() = default;

	void initalisePartition(std::array<TSPType, Size> const& Data) override {
		// Do nothing
	};

	std::vector<size_t> getCities(const Cube& s) const override {
		std::vector<size_t> output;
		output.reserve(Size);

		return output;
	};
};