#pragma once

#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_internal.h"
#include "wrapped/types.h"

namespace deadcell::gui {

    namespace colors {
        inline auto active_window_glow = color(210, 115, 138, 255);

        inline auto titlebar = color(30, 31, 41, 255);
        inline auto titlebar_text = color(199, 199, 199, 255);

        inline auto shadow = color(0, 0, 0, 255);

        inline auto body_dark = color(40, 42, 54, 255);
        inline auto body_darker = color(23, 25, 33, 255);

        inline auto border_light = color(52, 53, 62, 255);
        inline auto border_dark = color(27, 28, 37, 255);

        inline auto button_default = color(66, 68, 78);
    }

    namespace fonts {
        inline ImFont *titlebar_font = nullptr;

        inline ImFont *button_font = nullptr;
    }

}
