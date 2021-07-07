#pragma once

#include "thirdparty/imgui/imgui.h"
#include "wrapped/types.h"

namespace deadcell::gui {

    namespace colors {
        inline auto shadow = color(0, 0, 0, 255);

        inline auto white = color(222, 222, 222, 255);
        inline auto red = color(255, 85, 85, 255);
        inline auto green = color(80, 250, 123, 255);
        inline auto yellow = color(241, 250, 140, 255);

        inline auto active_window_glow = color(210, 115, 138, 255);

        inline auto titlebar = color(30, 31, 41, 255);
        inline auto titlebar_text = color(199, 199, 199, 255);

        inline auto body_dark = color(40, 42, 54, 255);
        inline auto body_darker = color(23, 25, 33, 255);

        inline auto border_light = color(52, 53, 62, 255);
        inline auto border_dark = color(27, 28, 37, 255);

        // Button
        inline auto button_body = color(66, 68, 78, 255);
        inline auto button_body_disabled = color(52, 54, 65);
        inline auto button_text = color(199, 199, 199, 255);
        inline auto button_text_disabled = color(132, 134, 140, 255);

        // Checkbox
        inline auto checkbox_unchecked_body = color(169, 170, 175);
        inline auto checkbox_unchecked_body_disabled = color(96, 97, 106);
        inline auto checkbox_checked_body = color(255, 121, 198);
        inline auto checkbox_checked_body_disabled = color(96, 97, 106);
        inline auto checkbox_check = color(40, 42, 54, 255);
        inline auto checkbox_text = color(199, 199, 199, 255);
        inline auto checkbox_text_disabled = color(122, 123, 130, 255);
    }

    namespace fonts {
        inline ImFont *icons_font = nullptr;

        inline ImFont *titlebar_font = nullptr;
        inline ImFont *button_font = nullptr;
        inline ImFont *checkbox_font = nullptr;
    }

}
