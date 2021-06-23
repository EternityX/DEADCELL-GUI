#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

namespace deadcell::gui {
    inline ImDrawList *fg_draw_list;
    inline ImDrawList *bg_draw_list;
}