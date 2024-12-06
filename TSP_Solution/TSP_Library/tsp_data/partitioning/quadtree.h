#pragma once
#include <array>
#include <vector>
#include <memory>

#include "../types/type_base.h"


class QuadTree {
public:
	QuadTree(Square area) : m_bounds(area), m_id(SIZE_MAX), m_point(P2DEFAULT) {};
	~QuadTree() = default;

	// TODO: optimise this function
	void insert(cityID id, Point2D point) {
		double x_mid = m_bounds.p.x + m_bounds.width / 2;
		double y_mid = m_bounds.p.y + m_bounds.height / 2;
		double width = m_bounds.width / 2;
		double height = m_bounds.height / 2;

		if (m_id == SIZE_MAX) {
			m_id = id;
			m_point = point;

			m_children[0] = std::make_unique<QuadTree>(Square{ m_bounds.p, width, height });	// Top left
			m_children[1] = std::make_unique<QuadTree>(Square{ Point2D{ x_mid, m_bounds.p.y }, width, height });	// Top right
			m_children[2] = std::make_unique<QuadTree>(Square{ Point2D{ m_bounds.p.x, y_mid }, width, height });	// Bottom left
			m_children[3] = std::make_unique<QuadTree>(Square{ Point2D{ x_mid, y_mid }, width, height });	// Bottom right
			return;
		}

		if (point.x < x_mid) {
			if (point.y < y_mid) {
				m_children[0]->insert(id, point); // Top left
			}
			else {
				m_children[2]->insert(id, point); // Bottom left
			}
		}
		else {
			if (point.y < y_mid) {
				m_children[1]->insert(id, point); // Top right
			}
			else {
				m_children[3]->insert(id, point); // Bottom right
			}
		}
	};

	
	std::vector<cityID> contains(const Square& search_area) {
		std::vector<cityID> found;
		_contains(search_area, found);
		return found;
	};

private:
	size_t m_id;
	Point2D m_point;
	const Square m_bounds;
	std::array<std::unique_ptr<QuadTree>, 4> m_children = { nullptr };
	
	// TODO: Optimise this function
	void _contains(const Square& search_area, std::vector<cityID>& found) {
		if (m_id == SIZE_MAX)
			return;

		if (search_area.overlaps(m_bounds)) {
			if (search_area.contains(m_point))
				found.push_back(m_id);

			m_children[0]->_contains(search_area, found);
			m_children[1]->_contains(search_area, found);
			m_children[2]->_contains(search_area, found);
			m_children[3]->_contains(search_area, found);
		}
	};
};
