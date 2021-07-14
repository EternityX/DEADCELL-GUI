/*
 * Copyright (c) 2021, EternityX <eternity@enevade.org>
 *
 * SPDX License Identifier: BSD-3-Clause
 */

#include "drawing.h"

#include <algorithm>

namespace deadcell::gui::drawing {
	static ImDrawList *internal_dl = nullptr;

	ImDrawList *get_draw_list() {
		return internal_dl;
	}

	void set_draw_list(const int draw_list) {
		switch (draw_list) {
		    case draw_list_background: internal_dl = ImGui::GetBackgroundDrawList(); break;
		    case draw_list_foreground: internal_dl = ImGui::GetForegroundDrawList(); break;
			default: break;
		}
	}

	point measure_text(ImFont *font, const float wrap_width, float font_size, const char *text) {
		if (font_size < 0.0f) {
			font_size = font->FontSize;
		}

		const auto size = font->CalcTextSizeA(font_size, std::numeric_limits<float>::max(), wrap_width, text);

		return { size.x, size.y };
	}

	void text(const point &position, const color &col, ImFont *font, const float wrap_width, float font_size, const char *text) {
		assert(internal_dl);
		assert(font);

		if (font_size < 0.0f) {
			font_size = font->FontSize;
		}

		internal_dl->AddText(font, font_size, { position.x, position.y }, col, text, nullptr, wrap_width);
	}

	void rect(const point &position, const point &size, const color &col, const float rounding, const int draw_flags, const float thickness) {
		assert(internal_dl);

		internal_dl->AddRect(position, { position.x + size.x, position.y + size.y }, col, rounding, draw_flags, thickness);
	}

	void rect_filled(const point &position, const point &size, const color &col, const float rounding, const int draw_flags) {
		assert(internal_dl);

		internal_dl->AddRectFilled(position, { position.x + size.x, position.y + size.y }, col, rounding, draw_flags);
	}

	void rect_shadow(const point &position, const point &size, const color &col, const point &shadow_offset, const float shadow_thickness, const float rounding, const int draw_flags) {
		assert(internal_dl);

		internal_dl->AddShadowRect(position, { position.x + size.x, position.y + size.y }, col, shadow_thickness, shadow_offset, draw_flags, rounding);
	}

	void circle_filled(const point &center, const float radius, const color &col, const int segments) {
		assert(internal_dl);

		internal_dl->AddCircleFilled({ center.x, center.y }, radius, col, segments);
	}

	void push_clip_rect(const point &position, const point &size, const bool intersect) {
		assert(internal_dl);

		internal_dl->PushClipRect(position, { position.x + size.x, position.y + size.y }, intersect);
	}

	void pop_clip_rect() {
		assert(internal_dl);

		internal_dl->PopClipRect();
	}
}
