#pragma once

#include "../gui.h"

namespace deadcell::gui::drawing {
    void set_draw_list(ImDrawList *draw_list);
    void rect_filled(ImVec2 min, ImVec2 max, ImU32 col, float round = 0.0f, ImDrawFlags f = ImDrawFlags_None);
    void rect_shadow(ImVec2 min, ImVec2 max, ImU32 col, float shadow_thickness, ImVec2 shadow_offset, ImDrawFlags f = ImDrawFlags_None, float rounding = 0.0f);
}