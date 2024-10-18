#pragma once

enum CachingType {
	Full,
	Partial,
	None
};

enum GenerationType {
	Rectangle,
	Circle,
	AreaCode
};

struct point {
	double x, y;
};

struct square {
	double x, y, width, height;
};

enum PartitioningType {
	NoPartitioning,
	QuadTree
};