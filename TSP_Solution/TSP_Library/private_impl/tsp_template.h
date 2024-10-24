#pragma once
#include "base_sources.h"

template <class TSPType, CachingType Caching, class Partitioning>
class TspTemplate {

public:
	TspTemplate() = default;
	TspDataTemplate<TSPType, Caching, Partitioning> t;
};
