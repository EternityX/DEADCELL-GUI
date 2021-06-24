#include "drawing.h"

#include <cmath>

namespace deadcell::gui::drawing {
    ImDrawList *dl = nullptr;

    void set_draw_list(ImDrawList* draw_list) {
        dl = draw_list;
    }

    void rect_filled(const ImVec2 min, const ImVec2 max, const ImU32 col, const float round, const ImDrawFlags f) {
        assert(dl);

        dl->AddRectFilled({ std::floor(min.x), std::floor(min.y) }, { std::floor(max.x + min.x), std::floor(max.y + min.y) },
            col, round, f);
    }
}
