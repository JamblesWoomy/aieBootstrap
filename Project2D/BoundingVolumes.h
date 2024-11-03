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
		return (min + max) * 0.5f;
	}
	Vector2 AABB::extents() const {//calculate half extents of AABB
		return { abs(max.x - min.x) * 0.5f, abs(max.y - min.y) * 0.5f };
	}

	std::vector<Vector2> AABB::corners() const { //return each corner of the AABB box
		std::vector<Vector2> corners(4);
		corners[0] = min;
		corners[1] = { min.x, max.y };
		corners[2] = max;
		corners[3] = { max.x, min.y };
	}

	void AABB::debugDraw(aie::Renderer2D* renderer)//draw a debug box for testing collisions
	{
		renderer->drawLine(min.x, min.y, max.x, min.y);
		renderer->drawLine(min.x, min.y, max.x, min.y);
		renderer->drawLine(min.x, min.y, max.x, min.y);
		renderer->drawLine(min.x, min.y, max.x, min.y);
	}

	void AABB::fit(const std::vector<Vector2>& points) {//fit an AABB around a bounding region given points
		min = { FLT_MAX, FLT_MAX };
		max = { FLT_MIN, FLT_MIN };

		for (auto& p : points) {
			min = ::min(min, p);
			max = ::max(max, p);
		}
	}

	bool AABB::overlaps(const Vector2& p) const {
		return !(p.x < min.x || p.y < min.y || p.x > max.x || p.y > max.y);
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