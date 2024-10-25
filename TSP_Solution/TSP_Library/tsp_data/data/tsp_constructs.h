#pragma once
#include <iostream>

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

enum PartitioningType {
	NoPartitioning,
	QuadTree
};

struct Point3D {
public:
	Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
	
	const double x, y, z;

	friend std::ostream &operator<<(std::ostream &os, const Point3D &point) {
		os << "Point3D(" << point.x << ", " << point.y << ", " << point.z << ")";
		return os;
	}
};

struct Point2D {
public:
	Point2D(double x, double y) : x(x), y(y) {}
	Point2D(Point3D& p) : x(p.x), y(p.y) {}				// Can downgrade but not upgrade
	Point2D(Point3D&& p) : x(p.x), y(p.y) {}			// Can downgrade but not upgrade

	const double x, y;

	friend std::ostream &operator<<(std::ostream &os, const Point2D &point) {
		os << "Point2D(" << point.x << ", " << point.y << ")";
		return os;
	}
};

struct Cube {
	Point3D p;
	double width, height, depth;
	bool contains(const Point3D &p2) const {
		return p2.x >= this->p.x && p2.x <= this->p.x + width &&
			   p2.y >= this->p.y && p2.y <= this->p.y + height &&
			   p2.z >= this->p.z && p2.z <= this->p.z + depth;
	}

	bool contains(const Point2D &p2) const {
		return p2.x >= this->p.x && p2.x <= this->p.x + width &&
			p2.y >= this->p.y && p2.y <= this->p.y + height;
	}
};