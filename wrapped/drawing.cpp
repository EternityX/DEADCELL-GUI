#include "drawing.h"

#include <algorithm>

namespace deadcell::gui::drawing {
    ImDrawList *dl = nullptr;

    void set_draw_list(ImDrawList* draw_list) {
        dl = draw_list;
    }

    void set_cursor(const int cursor) {
        ImGui::SetMouseCursor(cursor);
    }

    float alpha_fade(const float value, const float target, float rate, float rewind_rate) {
        const auto interval = 1.0f / (target < value ? rewind_rate : rate) * ImGui::GetIO().DeltaTime;
        const auto delta = target - value;

        return std::clamp(value + delta * interval, 0.0f, 1.0f);
    }

    ImFont *create_font_from_ttf(ImGuiIO &io, const uint8_t *ttf_data, const int ttf_data_size, const float size, 
        const int rasterizer_flags, const std::initializer_list<ImWchar> glyph_ranges) {
        ImFontConfig font_config;

        font_config.FontData = std::malloc(ttf_data_size);
        font_config.FontDataSize = ttf_data_size;
        font_config.SizePixels = size;
        font_config.GlyphRanges = glyph_ranges.size() == 0 ? nullptr : glyph_ranges.begin();
        font_config.FontBuilderFlags = rasterizer_flags;

        if (font_config.FontData) {
            std::memcpy(font_config.FontData, ttf_data, ttf_data_size);
        }

        return io.Fonts->AddFont(&font_config);
    }

    ImVec2 measure_text(ImFont *font, const float wrap_width, float font_size, const char *text) {
        if (font_size < 0.0f) {
            font_size = font->FontSize;
        }

        const auto size = font->CalcTextSizeA(font_size, FLT_MAX, wrap_width, text);

        return { size.x, size.y };
    }

    void text(const ImVec2 position, const ImU32 color, ImFont *font, const float wrap_width, float font_size, const char *text) {
        if (font_size < 0.0f) {
            font_size = font->FontSize;
        }

        dl->AddText(font, font_size, { position.x, position.y }, color, text, nullptr, wrap_width);
    }

    void rect_filled(const ImVec2 min, const ImVec2 max, const ImU32 col, const float round, const ImDrawFlags f) {
        assert(dl);

        dl->AddRectFilled({ std::floor(min.x), std::floor(min.y) }, { std::floor(max.x + min.x), std::floor(max.y + min.y) },
            col, round, f);
    }

    void rect_shadow(const ImVec2 min, const ImVec2 max, const ImU32 col, const float shadow_thickness, 
        const ImVec2 shadow_offset, const ImDrawFlags f, const float rounding) {
        assert(dl);

        dl->AddShadowRect({ std::floor(min.x), std::floor(min.y) }, { std::floor(max.x + min.x), std::floor(max.y + min.y) },
            col, shadow_thickness, shadow_offset, f, rounding);
    }
}
