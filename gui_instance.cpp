#include "gui_instance.h"
#include "thirdparty/material_icons.h"

deadcell::gui::gui_instance::gui_instance() {
    window_manager_ = std::make_unique<window_manager>();

    fonts::titlebar_font = platform::create_font_from_data(cerebri_sans_medium_ttf, sizeof(cerebri_sans_medium_ttf), 24.0f);
    fonts::button_font = platform::create_font_from_data(cerebri_sans_medium_ttf, sizeof(cerebri_sans_medium_ttf), 16.0f, 2);
    fonts::checkbox_font = platform::create_font_from_data(cerebri_sans_medium_ttf, sizeof(cerebri_sans_medium_ttf), 16.0f, 2);

    // TODO: Merge icon font with other fonts.
    fonts::icons_font = platform::create_font_from_data(material_icons_medium_ttf, sizeof(material_icons_medium_ttf), 16.0f, 0, { ICON_MIN_MD, ICON_MAX_MD, 0 });

    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->Build();

    set_dpi_scale(1.0f);

    initialized_ = true;
}

deadcell::gui::gui_instance::~gui_instance() {

}

void deadcell::gui::gui_instance::set_dpi_scale(const float scale) {
    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale = scale;
}
