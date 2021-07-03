#pragma once

#include "../thirdparty/imgui/imgui.h"

#include <cmath>

namespace deadcell::gui {

	struct color {
		unsigned char r, g, b, a;

		color() : r(255), g(255), b(255), a(255) {}
		color(int r, int g, int b, int a = 255) : r(r), g(g), b(b), a(a) {
			assert(r >= 0 && r <= 255);
			assert(g >= 0 && g <= 255);
			assert(b >= 0 && b <= 255);
			assert(a >= 0 && a <= 255);
		}

		color adjust_alpha(int new_alpha) const {
			assert(new_alpha >= 0 && new_alpha <= 255);

			return { r, g, b, new_alpha };
		}

		operator unsigned int() const {
			return IM_COL32(r, g, b, a);
		}

		// TODO: Color manipulation? Conversion between color spaces?
	};

	struct point {
		float x, y;

		point() :x(0.0f), y(0.0f) {}
		point(float val) :x(val), y(val) {}
		point(float x, float y) : x(x), y(y) {}

		operator ImVec2() const {
			return ImVec2(std::floor(x), std::floor(y));
		}

		bool is_empty() const {
			return x <= 0 && y <= 0 ? true : false;
		}

		// Mostly copied from imgui_internal.h line 340
		inline point operator+(const point& rhs) const { return point(x + rhs.x, y + rhs.y); }
		inline point operator-(const point& rhs) const { return point(x - rhs.x, y - rhs.y); }
		inline point operator*(const point& rhs) const { return point(x * rhs.x, y * rhs.y); }
		inline point operator/(const point& rhs) const { return point(x / rhs.x, y / rhs.y); }
		inline point operator+(float rhs) const { return point(x + rhs, y + rhs); }
		inline point operator-(float rhs) const { return point(x - rhs, y - rhs); }
		inline point operator*(float rhs) const { return point(x * rhs, y * rhs); }
		inline point operator/(float rhs) const { return point(x / rhs, y / rhs); }

		inline point& operator+=(const point& rhs) { x += rhs.x; y += rhs.y; return *this; }
		inline point& operator-=(const point& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
		inline point& operator*=(const point& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
		inline point& operator/=(const point& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
		inline point& operator+=(float rhs) { x += rhs; y += rhs; return *this; }
		inline point& operator-=(float rhs) { x -= rhs; y -= rhs; return *this; }
		inline point& operator*=(float rhs) { x *= rhs; y *= rhs; return *this; }
		inline point& operator/=(float rhs) { x /= rhs; y /= rhs; return *this; }

        bool operator>(const point &rhs) const { return x > rhs.x && y > rhs.y; }
		bool operator<(const point &rhs) const { return x < rhs.x && y < rhs.y; }
		bool operator>=(const point &rhs) const { return x >= rhs.x && y >= rhs.y; }
        bool operator<=(const point &rhs) const { return x <= rhs.x &&y <= rhs.y; }
    };

}
