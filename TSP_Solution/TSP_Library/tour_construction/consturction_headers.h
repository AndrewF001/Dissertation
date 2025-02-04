#pragma once
#include "static_lookahead_convex_hull.h"
#include "nearest_neighbour.h"
#include "shortest_insertion.h"
#include "convex_hull_insertion.h"
#include "static_lookahead.h"
#include "dynamic_lookahead.h"
#include "dynamic_lookahead_convex_hull.h"

enum class ConstructionType {
	DynamicLookahead,
	DynamicLookaheadConvexHullInserstion,
	StaticLookaheadConvexHullInserstion,
	StaticLookahead,
	NearestNeighbour,
	ShortestInsertion,
	ConvexHullInsertion,
	ConvexHull,
};