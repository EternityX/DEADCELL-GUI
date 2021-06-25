#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

namespace deadcell::gui {
    inline ImDrawList *fg_draw_list;
    inline ImDrawList *bg_draw_list;

    namespace color {
        inline auto active_window_glow = IM_COL32(210, 115, 138, 255);
        inline auto body_darker = IM_COL32(23, 23, 30, 255);
        inline auto body_dark = IM_COL32(27, 27, 34, 255);

        inline auto border_light = IM_COL32(52, 53, 62, 255);
    }
}