#pragma once

#include <memory>

#include "extra/window_manager.h"
#include "thirdparty/cerebri_sans_medium_ttf.h"
#include "thirdparty/material_icons_medium_ttf.h"
#include "wrapped/drawing.h"
#include "wrapped/platform.h"

namespace deadcell::gui {

    class gui_instance {
    private:
        bool initialized_ = false;

        std::shared_ptr<window_manager> window_manager_;

    public:
        gui_instance();

        ~gui_instance();

        void set_dpi_scale(float scale);

        // return pointer to window manager class
        std::shared_ptr<window_manager> wm() const {
            return window_manager_;
        }
    };

}
