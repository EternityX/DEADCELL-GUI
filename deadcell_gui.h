#pragma once

#include <memory>

#include "extra/window_manager.h"
#include "vendor/cerebri_sans_medium_ttf.h"
#include "vendor/material_icons_medium_ttf.h"
#include "wrapped/drawing.h"
#include "wrapped/platform.h"

namespace deadcell::gui {
    class deadcell_gui {
    private:
        bool initialized_ = false;

        std::shared_ptr<window_manager> window_manager_;

    public:
        deadcell_gui();

        ~deadcell_gui();

        static void set_dpi_scale(float scale);

        // return pointer to window manager class
        std::shared_ptr<window_manager> wm() const {
            return window_manager_;
        }
    };
}
