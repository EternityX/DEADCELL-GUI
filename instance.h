#pragma once

#include <memory>

#include "extra/window_manager.h"
#include "thirdparty/cerebri_sans_medium_ttf.h"
#include "wrapped/drawing.h"

namespace deadcell::gui {
    class instance {
    private:
        bool initialized_ = false;
        std::shared_ptr<window_manager> window_manager_;

    public:
        instance() {
            auto &io = ImGui::GetIO();

            window_manager_ = std::make_unique<window_manager>();

            font::titlebar_font = drawing::create_font_from_ttf(io, cerebri_sans_medium_ttf, sizeof(cerebri_sans_medium_ttf), 24.0f);

            initialized_ = true;
        }

        ~instance() {

        }

        // return pointer to window manager class
        std::shared_ptr<window_manager> wm() const {
            return window_manager_;
        }
    };
}
