#pragma once

#include <memory>

#include "extra/window_manager.h"
#include "thirdparty/cerebri_sans_medium_ttf.h"
#include "wrapped/drawing.h"
#include "wrapped/platform.h"

namespace deadcell::gui {

    class gui_instance {
    private:
        bool initialized_ = false;

        std::shared_ptr<window_manager> window_manager_;

    public:
        gui_instance() {
            window_manager_ = std::make_unique<window_manager>();

            fonts::titlebar_font = platform::create_font_from_data(cerebri_sans_medium_ttf, sizeof(cerebri_sans_medium_ttf), 24.0f);

            initialized_ = true;
        }

        ~gui_instance() {

        }

        // return pointer to window manager class
        std::shared_ptr<window_manager> wm() const {
            return window_manager_;
        }
    };

}
