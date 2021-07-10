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

        template <typename T, typename... Args>
        auto add(Args... args) {
            return std::make_shared<T>(args...);
        }

        static void set_dpi_scale(float scale);

        // return pointer to window manager class
        auto wm() const {
            return window_manager_;
        }
    };

    std::shared_ptr<deadcell_gui> create();
}
