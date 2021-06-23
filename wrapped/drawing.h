#pragma once

#include "../gui.h"

namespace deadcell::gui::drawing {
    void set_draw_list(ImDrawList *draw_list);
    void rect_filled(ImVec2 min, ImVec2 max, ImU32 col, float round, ImDrawFlags f);
}