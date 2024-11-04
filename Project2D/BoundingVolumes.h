#include <vector.h>
#include <matrix.h>
#include <vector>
#include <cassert>
#include "Application2D.h"
#include "Renderer2D.h"

class AABB {
public:
	AABB() {}
	AABB(const Vector2& min, const Vector2& max) : m_min(min), m_max(max) {};
	Vector2 m_min, m_max;
	Vector2 AABB::center() const {// find the center position of the AABB
		return (m_min + m_max) * 0.5f;
	}
	Vector2 AABB::extents() const {//calculate half extents of AABB
		return { abs(m_min.x - m_min.x) * 0.5f, abs(m_max.y - m_max.y) * 0.5f };
	}

	std::vector<Vector2> AABB::corners() const { //return each corner of the AABB box
		std::vector<Vector2> corners(4);
		corners[0] = m_min;
		corners[1] = { m_min.x, m_max.y };
		corners[2] = m_max;
		corners[3] = { m_max.x, m_min.y };
	}

	void AABB::debugDraw(aie::Renderer2D* renderer)//draw a debug box for testing collisions
	{
		renderer->drawLine(m_min.x, m_min.y, m_max.x, m_min.y);
		renderer->drawLine(m_max.x, m_min.y, m_max.x, m_max.y);
		renderer->drawLine(m_max.x, m_max.y, m_min.x, m_max.y);
		renderer->drawLine(m_min.x, m_max.y, m_min.x, m_min.y);
	}

	void AABB::fit(const Vector2* points, unsigned int count) {//fit an AABB around a bounding region given points
		m_min = { FLT_MAX, FLT_MAX };
		m_max = { FLT_MIN, FLT_MIN };

		for (unsigned int i = 0; i < count; ++i, ++points) {
			m_min = std::min(m_min, *points);
			m_max = std::max(m_max, *points);
		}
	}

	bool AABB::overlaps(const Vector2& p) const {//check if two AABBs overlap with one another
		return !(p.x < m_min.x || p.y < m_min.y || p.x > m_max.x || p.y > m_max.y);
	}

private:
	float min(float a, float b) { return a < b ? a : b; }
	float max(float a, float b) { return a > b ? a : b; }
	Vector2 AABB::min(const Vector2& a, const Vector2& b) {
		return { min(a.x, b.x), min(a.y, b.y) };
	}
	Vector2 AABB::max(const Vector2& a, const Vector2& b) {
		return { max(a.x, b.x), max(a.y, b.y) };
	}

	float AABB::clamp(float t, float a, float b) {
		return max(a, min(b, t));
	}
	Vector2 AABB::clamp(const Vector2& t, const Vector2& a, const Vector2& b) {
		return max(a, min(b, t));
	}
};