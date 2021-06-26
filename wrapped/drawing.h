#pragma once

#include <cmath>

#include "../gui.h"

namespace deadcell::gui::drawing {
    void set_draw_list(ImDrawList *draw_list);
    void set_cursor(int cursor);
    float alpha_fade(float value, float target, float rate = 0.065f, float rewind_rate = 0.09f);
    ImFont *create_font_from_ttf(ImGuiIO &io, const uint8_t *ttf_data, int ttf_data_size, float size, int rasterizer_flags = 0, std::initializer_list<ImWchar> glyph_ranges = { });
    ImVec2 measure_text(ImFont *font, float wrap_width, float font_size, const char *text);
    void text(ImVec2 position, ImU32 color, ImFont *font, float wrap_width, float font_size, const char *text);
    void rect_filled(ImVec2 position, ImVec2 size, ImU32 col, float round = 0.0f, ImDrawFlags f = ImDrawFlags_None);
    void rect_shadow(ImVec2 position, ImVec2 size, ImU32 col, float shadow_thickness, ImVec2 shadow_offset, ImDrawFlags f = ImDrawFlags_None, float rounding = 0.0f);
}
