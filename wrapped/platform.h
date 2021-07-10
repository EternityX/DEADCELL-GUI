#pragma once

#include "../vendor/imgui/imgui.h"

#include <algorithm>
#include <initializer_list>

namespace deadcell::gui::platform {
	enum cursor_e {
        cursor_none = -1,
        cursor_arrow = 0,
        cursor_text_input,
        cursor_resize_all,
        cursor_resize_ns,
        cursor_resize_ew,
        cursor_resize_nesw,
        cursor_resize_nwse,
        cursor_hand,
        cursor_not_allowed,
	};

    inline float fade(float value, float target, float rate = 0.065f, float rewind_rate = 0.09f, float min = 0.0f, float max = 1.0f) {
        const auto interval = 1.0f / (target < value ? rewind_rate : rate) * ImGui::GetIO().DeltaTime;
        const auto delta = target - value;

        return std::clamp(value + delta * interval, min, max);
    }

	void set_cursor(int cursor);

	float get_frame_time();

    ImFont* create_font_from_data(const void* font_data, int font_data_size, float size, int rasterizer_flags = 0, std::initializer_list<ImWchar> glyph_ranges = { });
}
