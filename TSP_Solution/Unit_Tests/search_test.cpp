#include "pch.h"
#include "gtest/gtest.h"
#include "tsp_data/tsp_data_template.h"
#include <tsp_data/types/2d.h>

TEST(SearchArea, Creation) {
	TspDataTemplate<Type2d, 10, CachingType::full, PartitioningType::linearSearch> data({ {0, 0}, 100, 100 });
	//data.addCity({ 50, 50 });
}