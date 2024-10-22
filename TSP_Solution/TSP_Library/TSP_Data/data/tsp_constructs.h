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

struct Point {
	double x, y;
};

struct Square {
	Point p;
	double width, height;
	bool contains(const Point &p2) const {
		return p2.x >= this->p.x && p2.x <= this->p.x + width &&
			   p2.y >= this->p.y && p2.y <= this->p.y + height;
	}
};

enum PartitioningType {
	NoPartitioning,
	QuadTree
};