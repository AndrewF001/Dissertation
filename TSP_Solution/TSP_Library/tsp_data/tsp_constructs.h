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
	//noPartitioning,
	linearSearch,
	quadTree,
};

struct Point2D {
public:
	Point2D(double x = 0, double y = 0) : m_x(x), m_y(y) {}
	Point2D(Point2D const& p) : m_x(p.m_x), m_y(p.m_y) {}
	//explicit Point2D(Point2D&& p) : x(p.x), y(p.y) {}	// TODO: Add Rvalue reference constructor

	double m_x, m_y;	// TODO: This should be const

	double gradient(const Point2D& p2) const {
		auto d = (p2.m_x - m_x);
		if (d == 0)
			return INFINITY;
		return (p2.m_y - m_y) / d;
	}

	friend std::ostream& operator<<(std::ostream& os, const Point2D& point) {
		os << "Point2D(" << point.m_x << ", " << point.m_y << ")";
		return os;
	}
};

static Point2D const P2DEFAULT = Point2D(0, 0);

struct Square {
	Square(Square const& c) : m_p1(c.m_p1), m_p2(c.m_p2) {}

	Square(Point2D const& p1, Point2D const& p2) {
		if (p1.m_x < p2.m_x) {
			m_p1.m_x = p1.m_x;
			m_p2.m_x = p2.m_x;
		}
		else {
			m_p1.m_x = p2.m_x;
			m_p2.m_x = p1.m_x;
		}

		if (p1.m_y < p2.m_y) {
			m_p1.m_y = p1.m_y;
			m_p2.m_y = p2.m_y;
		}
		else {
			m_p1.m_y = p2.m_y;
			m_p2.m_y = p1.m_y;
		}
	}

	Square(Point2D const& p = P2DEFAULT, double width = 0, double height = 0) {
		if (width < 0) {
			m_p1.m_x = p.m_x + width;
			m_p2.m_x = p.m_x;
		} else {
			m_p1.m_x = p.m_x;
			m_p2.m_x = p.m_x + width;
		}

		if (width == INFINITY)
			m_p2.m_x = INFINITY;

		if (height < 0) {
			m_p1.m_y = p.m_y + height;
			m_p2.m_y = p.m_y;
		} else {
			m_p1.m_y = p.m_y;
			m_p2.m_y = p.m_y + height;
		}

		if (height == INFINITY)
			m_p2.m_y = INFINITY;
	}

	Point2D m_p1;
	Point2D m_p2;	// Using this instead of width and height to deal with double precision errors and negative values

	bool contains(const Point2D& point) const {
		bool x = point.m_x >= m_p1.m_x &&
				 point.m_x <= m_p2.m_x;

		bool y = point.m_y >= m_p1.m_y &&
				 point.m_y <= m_p2.m_y;

		return x && y;
	}

	bool overlaps(const Square& s) const {
		bool x = m_p1.m_x <= s.m_p2.m_x &&
				 m_p2.m_x >= s.m_p1.m_x;

		bool y = m_p1.m_y <= s.m_p2.m_y &&
				 m_p2.m_y >= s.m_p1.m_y;

		return x && y;
	}

	double width() const {
		return m_p2.m_x - m_p1.m_x;
	}

	double height() const {
		return m_p2.m_y - m_p1.m_y;
	}

	friend std::ostream& operator<<(std::ostream& os, const Square& point) {
		os << "Square(" << point.m_p1.m_x << ", " << point.m_p1.m_y << " : " << point.m_p2.m_x << ", " << point.m_p2.m_y << ")";
		return os;
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
