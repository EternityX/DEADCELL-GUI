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
        drawing::rect_filled(get_position(), get_size(), color::border_light, 0.0f, 0);
        drawing::rect_filled(get_position() + ImVec2(1, 1), get_size() - ImVec2(1, 1), color::body_darker, 0.0f, 0);
        
    }
}
