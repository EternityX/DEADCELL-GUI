/*
 * Copyright (c) 2021, EternityX <jeramie@protonmail.com>
 *
 * SPDX License Identifier: BSD-3-Clause
 */

#pragma once

#include "vendor/imgui/imgui.h"
#include "wrapped/types.h"

namespace deadcell::gui {
    namespace colors {
        inline auto shadow = color(0, 0, 0);

        inline auto white = color(222, 222, 222);
        inline auto red = color(255, 85, 85);
        inline auto green = color(80, 250, 123);
        inline auto yellow = color(241, 250, 140);
        inline auto pink = color(255, 121, 198);

        inline auto active_window_glow = color(210, 115, 138);

        inline auto titlebar = color(30, 31, 41);
        inline auto titlebar_text = color(199, 199, 199);

        inline auto body_lighter = color(43, 44, 56);
        inline auto body_dark = color(30, 31, 41);
        inline auto body_darker = color(23, 25, 33);

        inline auto border_light = color(52, 53, 62);
        inline auto border_dark = color(27, 28, 37);

        // Button
        inline auto button_body = color(40, 42, 54);
        inline auto button_body_disabled = color(34, 35, 46);
        inline auto button_text = color(199, 199, 199);
        inline auto button_text_disabled = color(132, 134, 140);

        // Checkbox
        inline auto checkbox_background = color(68, 71, 93);
        inline auto checkbox_text = color(199, 199, 199);
        inline auto checkbox_text_disabled = color(122, 123, 130);

        // Progressbar
        inline auto progress_background = color(52, 54, 65);
        inline auto progress_filled = color(255, 121, 198);
        inline auto progress_text = color(199, 199, 199);
    }

    namespace fonts {
        inline ImFont *icons_font = nullptr;

        inline ImFont *titlebar_font = nullptr;
        inline ImFont *button_font = nullptr;
        inline ImFont *checkbox_font = nullptr;
    }
}
