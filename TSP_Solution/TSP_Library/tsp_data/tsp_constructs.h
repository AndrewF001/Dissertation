#pragma once
#include <iostream>

enum CachingTypes {
	FULL,
	Partial,
	None
};

enum GenerationTypes {
	Rectangle,
	Circle,
	AreaCode
};

enum PartitioningTypes {
	NonePartitioning,
	QuadTree
};

struct Point2D;

struct Point3D {
public:
	Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
	Point3D(Point2D const& p);
	Point3D(Point2D&& p);

	double x, y, z;	// TODO: This should be const

	friend std::ostream& operator<<(std::ostream& os, const Point3D& point) {
		os << "Point3D(" << point.x << ", " << point.y << ", " << point.z << ")";
		return os;
	}
};

struct Point2D {
public:
	Point2D(double x, double y) : x(x), y(y) {}
	Point2D(Point3D const& p) : x(p.x), y(p.y) {}
	Point2D(Point3D&& p) : x(p.x), y(p.y) {}

	double x, y;	// TODO: This should be const

	friend std::ostream& operator<<(std::ostream& os, const Point2D& point) {
		os << "Point2D(" << point.x << ", " << point.y << ")";
		return os;
	}
};

Point3D::Point3D(Point2D const& p) : x(p.x), y(p.y), z(0) {}
Point3D::Point3D(Point2D&& p) : x(p.x), y(p.y), z(0) {}

static Point2D const P2DEFAULT = Point2D(0, 0);
static Point3D const P3DEFAULT = Point3D(0, 0, 0);

struct Cube {
	Cube(Cube const& c) : p(c.p), width(c.width), height(c.height), depth(c.depth) {}
	Cube(Point2D const& p = P2DEFAULT, double width = 0, double height = 0, double depth = 0) : p(p), width(width), height(height), depth(0) {}
	Cube(Point3D const& p = P3DEFAULT, double width = 0, double height = 0, double depth = 0) : p(p), width(width), height(height), depth(depth) {}


	Point3D p;
	double width, height, depth;

	bool contains(const Point3D& p2) const {
		return p2.x >= this->p.x && p2.x <= this->p.x + width &&
			p2.y >= this->p.y && p2.y <= this->p.y + height &&
			p2.z >= this->p.z && p2.z <= this->p.z + depth;
	}

	bool contains(const Point2D& p2) const {
		return p2.x >= this->p.x && p2.x <= this->p.x + width &&
			p2.y >= this->p.y && p2.y <= this->p.y + height;
	}
};
