#pragma once

#include "extra/window_manager.h"

#include <memory>

namespace deadcell::gui {
    class instance {
    private:
        bool initialized_ = false;
        std::shared_ptr<window_manager> window_manager_;

    public:
        instance() {
            window_manager_ = std::make_unique<window_manager>();
            initialized_ = true;
        }

        ~instance() {

        }

        std::shared_ptr<window_manager> get_window_manager() const {
            return window_manager_;
        }
    };
}