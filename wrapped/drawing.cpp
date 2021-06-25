#include "drawing.h"

#include <cmath>

namespace deadcell::gui::drawing {
    ImDrawList *dl = nullptr;

    void set_draw_list(ImDrawList* draw_list) {
        dl = draw_list;
    }

    void rect_filled(const ImVec2 min, const ImVec2 max, const ImU32 col, const float round, const ImDrawFlags f) {
        assert(dl);

        dl->AddRectFilled({ std::floor(min.x), std::floor(min.y) }, { std::floor(max.x), std::floor(max.y) },
            col, round, f);
    }

    void rect_shadow(const ImVec2 min, const ImVec2 max, const ImU32 col, const float shadow_thickness, 
        const ImVec2 shadow_offset, const ImDrawFlags f, const float rounding) {

        assert(dl);

        dl->AddShadowRect({ std::floor(min.x), std::floor(min.y) }, { std::floor(max.x), std::floor(max.y) },
            col, shadow_thickness, shadow_offset, f, rounding);
    }
}
