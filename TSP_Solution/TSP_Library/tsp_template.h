#pragma once
#include "tsp_data/data/tsp_data_template.h"
#include "tsp_data/data/types/type_base.h"
#include "tsp_data/data/types/type_base.cpp"
#include "tsp_data/data/types/2d.h"
#include "tsp_data/data/types/2d.cpp"

template <class TSPType, CachingType Caching, class Partitioning>
class TspTemplate {

public:
	TspTemplate() = default;
	TspDataTemplate<TSPType, Caching, Partitioning> t;
};
