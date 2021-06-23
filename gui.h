#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#include <imgui_internal.h>

#include "layout.h"

#include <d3d9.h>

namespace deadcell::gui {
    inline ImDrawList *fg_draw_list;
    inline ImDrawList *bg_draw_list;

    inline IDirect3DDevice9 *d3d_device;

    namespace colors {
        inline auto titlebar = IM_COL32(30, 31, 41, 255);
        inline auto sidebar = IM_COL32(30, 31, 41, 255);
        inline auto border = IM_COL32(23, 24, 31, 255);
        inline auto content = IM_COL32(40, 42, 54, 255);

        inline auto shadow = IM_COL32(0, 0, 0, 255);
    }
}