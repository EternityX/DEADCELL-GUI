/*
Copyright (c) 2021, EternityX (jeramie@protonmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "deadcell_gui.h"

#include "vendor/material_icons.h"

namespace deadcell {
    gui::deadcell_gui::deadcell_gui() {
        IMGUI_CHECKVERSION();

        window_manager_ = std::make_unique<window_manager>();

        fonts::titlebar_font = platform::create_font_from_data(cerebri_sans_medium_ttf, sizeof(cerebri_sans_medium_ttf), 24.0f);
        fonts::button_font = platform::create_font_from_data(cerebri_sans_medium_ttf, sizeof(cerebri_sans_medium_ttf), 16.0f, 2);
        fonts::checkbox_font = platform::create_font_from_data(cerebri_sans_medium_ttf, sizeof(cerebri_sans_medium_ttf), 16.0f, 2);

        // TODO: Merge icon font with other fonts.
        fonts::icons_font = platform::create_font_from_data(material_icons_medium_ttf, sizeof(material_icons_medium_ttf), 15.0f, 32, { ICON_MIN_MD, ICON_MAX_MD, 0 });

        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->Build();

        set_dpi_scale(1.0f);

        initialized_ = true;
    }

    gui::deadcell_gui::~deadcell_gui() = default;

    void gui::deadcell_gui::set_dpi_scale(const float scale) {
        ImGuiIO &io = ImGui::GetIO();
        io.FontGlobalScale = scale;
    }
}
