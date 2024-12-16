#pragma once
#include <iostream>

using cityID = size_t;

enum CachingType {
	full,
	partial,
	none
};

enum GenerationType {
	rectangle,
	circle,
	areaCode
};

enum PartitioningType {
	noPartitioning,
	linearSearch,
	quadTree,
};

struct Point2D {
public:
	Point2D(double x = 0, double y = 0) : x(x), y(y) {}
	Point2D(Point2D const& p) : x(p.x), y(p.y) {}
	//explicit Point2D(Point2D&& p) : x(p.x), y(p.y) {}	// TODO: Add Rvalue reference constructor

	double x, y;	// TODO: This should be const

	double gradient(const Point2D& p2) const {
		return (p2.y - y) / (p2.x - x);
	}

	friend std::ostream& operator<<(std::ostream& os, const Point2D& point) {
		os << "Point2D(" << point.x << ", " << point.y << ")";
		return os;
	}
};

static Point2D const P2DEFAULT = Point2D(0, 0);

struct Square {
	Square(Square const& c) : p(c.p), width(c.width), height(c.height) {}
	Square(Point2D const& p = P2DEFAULT, double width = 0, double height = 0) : p(p), width(width), height(height) {}


	Point2D p;
	double width, height;

	bool contains(const Point2D& p2) const {
		bool x = p2.x >= p.x;
		if (width != INFINITY)
			x = x && p2.x <= p.x + width;

		bool y = p2.y >= p.y;
		if (height != INFINITY)
			y = y && p2.y <= p.y + height;


		return x && y;
	}

	bool overlaps(const Square& s) const {
		bool x = true;
		if (s.width != INFINITY)
			x = p.x < s.p.x + s.width;
		if (width != INFINITY)
			x &= p.x + width >= s.p.x;

		bool y = true;
		if (s.height != INFINITY)
			y = p.y < s.p.y + s.height;
		if (height != INFINITY)
			y &= p.y + height >= s.p.y;

		return x && y;
	}
};

// TODO: 3D Code for later
/*
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

//Point3D::Point3D(Point2D const& p) : x(p.x), y(p.y), z(0) {}
//Point3D::Point3D(Point2D&& p) : x(p.x), y(p.y), z(0) {}

//static Point3D const P3DEFAULT = Point3D(0, 0, 0);

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
*/
