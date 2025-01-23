#pragma once
#include "static_lookahead_convex_hull.h"
#include "nearest_neighbour.h"
#include "shortest_insertion.h"
#include "convex_hull_insertion.h"

enum class ConstructionType {
	StaticLookaheadConvexHullInserstion,
	NearestNeighbour,
	ShortestInsertion,
	ConvexHullInsertion,
	ConvexHull,
};