#include "drawing.h"

#include <algorithm>

namespace deadcell::gui::drawing {
	static ImDrawList* dl = nullptr;

	void set_draw_list(int draw_list) {
		switch (draw_list) {
		case draw_list_background: dl = ImGui::GetBackgroundDrawList(); break;
		case draw_list_foreground: dl = ImGui::GetForegroundDrawList(); break;
		}
	}

	point measure_text(ImFont* font, const float wrap_width, float font_size, const char* text) {
		if (font_size < 0.0f) {
			font_size = font->FontSize;
		}

		const auto size = font->CalcTextSizeA(font_size, FLT_MAX, wrap_width, text);

		return { size.x, size.y };
	}

	void text(const point& position, const color& col, ImFont* font, const float wrap_width, float font_size, const char* text) {
		assert(dl);

		if (font_size < 0.0f) {
			font_size = font->FontSize;
		}

		dl->AddText(font, font_size, { position.x, position.y }, col, text, nullptr, wrap_width);
	}

	void rect_filled(const point& position, const point& size, const color& col, float rounding, int draw_flags) {
		assert(dl);

		dl->AddRectFilled(position, position + size, col, rounding, draw_flags);
	}

	void rect_shadow(const point& position, const point& size, const color& col, const point& shadow_offset, float shadow_thickness, float rounding, int draw_flags) {
		assert(dl);

		dl->AddShadowRect(position, position + size, col, shadow_thickness, shadow_offset, draw_flags, rounding);
	}

	void fill_circle(const point &center, const float radius, const color& col, const int segments) {
		assert(dl);

		dl->AddCircleFilled({ center.x, center.y }, radius, col, segments);
	}

	void push_clip_rect(const point &position, const point &size, const bool intersect) {
		assert(dl);

		dl->PushClipRect(position, { position.x + size.x, position.y + size.y }, intersect);
	}

	void pop_clip_rect() {
		assert(dl);

		dl->PopClipRect();
	}
}
