#pragma once

#include <cmath>

#include "../config.h"
#include "types.h"

namespace deadcell::gui::drawing {
	enum draw_list_e {
		draw_list_background,
		draw_list_foreground,
	};

	enum draw_flags_e {
		draw_flags_none = 0,
		draw_flags_closed = 1 << 0,
		draw_flags_round_top_left = 1 << 4,
		draw_flags_round_top_right = 1 << 5,
		draw_flags_round_bottom_left = 1 << 6,
		draw_flags_round_bottom_right = 1 << 7,
		draw_flags_round_none = 1 << 8,
		draw_flags_round_top = draw_flags_round_top_left | draw_flags_round_top_right,
		draw_flags_round_bottom = draw_flags_round_bottom_left | draw_flags_round_bottom_right,
		draw_flags_round_left = draw_flags_round_bottom_left | draw_flags_round_top_left,
		draw_flags_round_right = draw_flags_round_bottom_right | draw_flags_round_top_right,
		draw_flags_round_all = draw_flags_round_top_left | draw_flags_round_top_right | draw_flags_round_bottom_left | draw_flags_round_bottom_right,
		draw_flags_round_default_ = draw_flags_round_all,
		draw_flags_round_mask_ = draw_flags_round_all | draw_flags_round_none,
		draw_flags_shadow_cut_out_shape_background = 1 << 9,
	};

	enum draw_list_flags_e {
		draw_list_flags_none = 0,
		draw_list_flags_anti_aliased_lines = 1 << 0,
		draw_list_flags_anti_aliased_fill = 1 << 1,
	};

	ImDrawList *get_draw_list();
	void set_draw_list(int draw_list);
	point measure_text(ImFont *font, float wrap_width, float font_size, const char *text);
	void text(const point& position, const color& col, ImFont* font, float wrap_width, float font_size, const char* text);
	void rect(const point &position, const point &size, const color &col, float rounding = 0.0f, int draw_flags = draw_flags_none, float thickness = 1.0f);
	void rect_filled(const point& position, const point& size, const color& col, float rounding = 0.0f, int draw_flags = draw_flags_none);
	void rect_shadow(const point& position, const point& size, const color& col, const point& shadow_offset, float shadow_thickness, float rounding = 0.0f, int draw_flags = draw_flags_none);
	void circle_filled(const point &center, float radius, const color &col, int segments = 0);
    void push_clip_rect(const point &position, const point &size, bool intersect = false);
    void pop_clip_rect();
}
