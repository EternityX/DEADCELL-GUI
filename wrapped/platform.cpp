#include "platform.h"

namespace deadcell::gui::platform {

    void set_cursor(int cursor) {
        ImGui::SetMouseCursor(cursor);
    }

    float get_frame_time() {
        return ImGui::GetIO().DeltaTime;
    }

    ImFont* create_font_from_data(const void* font_data, int font_data_size, float size, int rasterizer_flags, std::initializer_list<ImWchar> glyph_ranges) {
        ImFontConfig font_config;

        font_config.FontData = std::malloc(font_data_size);
        font_config.FontDataSize = font_data_size;
        font_config.SizePixels = size;
        font_config.GlyphRanges = glyph_ranges.size() == 0 ? nullptr : glyph_ranges.begin();
        font_config.FontBuilderFlags = rasterizer_flags;

        if (font_config.FontData) {
            std::memcpy(font_config.FontData, font_data, font_data_size);
        }

        return ImGui::GetIO().Fonts->AddFont(&font_config);
    }

}
