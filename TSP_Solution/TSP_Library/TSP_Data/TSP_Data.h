#pragma once
// Bases
#include "data/tsp_data_template.h"
#include "data/tsp_data_template.cpp"
#include "data/tsp_data_realtime.h"
#include "data/tsp_constructs.h"
#include "partitioning/partitioning_base.h"
#include "types/type_base.h"
#include "types/2d.h"
#include "types/2d.cpp"

// Derived explicit instantiations

//template class TspDataTemplate<Type2d, CachingType::None, int>;	