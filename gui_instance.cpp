#include "gui_instance.h"

deadcell::gui::gui_instance::gui_instance() {
    window_manager_ = std::make_unique<window_manager>();

    fonts::titlebar_font = platform::create_font_from_data(cerebri_sans_medium_ttf, sizeof(cerebri_sans_medium_ttf), 24.0f);
    fonts::button_font = platform::create_font_from_data(cerebri_sans_medium_ttf, sizeof(cerebri_sans_medium_ttf), 16.0f);

    set_dpi_scale(1.0f);

    initialized_ = true;
}

deadcell::gui::gui_instance::~gui_instance() {

}

void deadcell::gui::gui_instance::set_dpi_scale(const float scale) {
    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale = scale;
}
