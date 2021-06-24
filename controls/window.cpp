#include "window.h"

#include "../wrapped/drawing.h"

namespace deadcell::gui {
    window::window(const std::string_view unique_id) {
        unique_ids_.insert(std::pair(unique_id, this));
    }

    void window::event(const base_event &e) {
        const auto &io = ImGui::GetIO();

        // NOLINT(clang-diagnostic-float-equal)
        if (io.MousePos.x != last_mouse_pos_.x || io.MousePos.y != last_mouse_pos_.y) {
            if (dragging_) {
                min_ = min_ + (io.MousePos - drag_start_);
            }
        }

        if (e.type() == window_event::left_mouse_down) {
            dragging_ = true;
            drag_start_ = { io.MousePos.x, io.MousePos.y };
        }

        if (e.type() == window_event::left_mouse_up) {
            if (dragging_) {
                dragging_ = false;
            }
        }

        last_mouse_pos_ = io.MousePos;
    }

    void window::render() {
        drawing::rect_filled(min_, max_, IM_COL32(255, 255, 255, 255), 0.0f, 0);
        drawing::rect_filled(min_, max_, IM_COL32(0, 255, 255, 255), 23.0f, 0);
    }
}
