#pragma once

#include "../thirdparty/imgui/imgui.h"

#include <cmath>

namespace deadcell::gui {
	struct color {
		unsigned char r, g, b, a;

		color() : r(255), g(255), b(255), a(255) {}
		color(const int _r, const int _g, const int _b, const int _a = 255) : r(_r), g(_g), b(_b), a(_a) {
			assert(_r >= 0 && _r <= 255);
			assert(_g >= 0 && _g <= 255);
			assert(_b >= 0 && _b <= 255);
			assert(_a >= 0 && _a <= 255);
		}

		color adjust_alpha(const int new_alpha) const {
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
		point(const float val) :x(val), y(val) {}
		point(const float x, const float y) : x(x), y(y) {}

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
		inline point operator+(const float rhs) const { return point(x + rhs, y + rhs); }
		inline point operator-(const float rhs) const { return point(x - rhs, y - rhs); }
		inline point operator*(const float rhs) const { return point(x * rhs, y * rhs); }
		inline point operator/(const float rhs) const { return point(x / rhs, y / rhs); }

		inline point& operator+=(const point& rhs) { x += rhs.x; y += rhs.y; return *this; }
		inline point& operator-=(const point& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
		inline point& operator*=(const point& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
		inline point& operator/=(const point& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
		inline point& operator+=(const float rhs) { x += rhs; y += rhs; return *this; }
		inline point& operator-=(const float rhs) { x -= rhs; y -= rhs; return *this; }
		inline point& operator*=(const float rhs) { x *= rhs; y *= rhs; return *this; }
		inline point& operator/=(const float rhs) { x /= rhs; y /= rhs; return *this; }

        bool operator>(const point &rhs) const { return x > rhs.x && y > rhs.y; }
		bool operator<(const point &rhs) const { return x < rhs.x && y < rhs.y; }
		bool operator>=(const point &rhs) const { return x >= rhs.x && y >= rhs.y; }
        bool operator<=(const point &rhs) const { return x <= rhs.x && y <= rhs.y; }
		bool operator!=(const point &rhs) const { return x != rhs.x || y != rhs.y; }  // NOLINT(clang-diagnostic-float-equal)
    };
}
