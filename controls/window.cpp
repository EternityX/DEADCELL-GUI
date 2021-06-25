#include "window.h"

#include <algorithm>

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"

namespace deadcell::gui {
    window::window(const std::string_view unique_id) {
        unique_ids_.insert(std::pair(unique_id, this));
    }

    void window::event(const base_event &e) {
        const auto &io = ImGui::GetIO();

        if (io.MousePos.x != last_mouse_pos_.x || io.MousePos.y != last_mouse_pos_.y) { // NOLINT(clang-diagnostic-float-equal)
            if (dragging_) {
                min_ = io.MousePos - drag_start_;

                min_.x = std::clamp(min_.x, 2.0f, io.DisplaySize.x - max_.x - 2.0f);
                min_.y = std::clamp(min_.y, 2.0f, io.DisplaySize.y - max_.y - 2.0f);
            }

            if (resizing_) {
                max_ = io.MousePos - resize_start_;

                max_.x = std::clamp(max_.x, min_size_.x, io.DisplaySize.x - min_.x - 2.0f);
                max_.y = std::clamp(max_.y, min_size_.y, io.DisplaySize.y - min_.y - 2.0f);
            }
        }

        if (e.type() == window_event::drag_start) {
            dragging_ = true;
            drag_start_ = io.MousePos - min_;
        }

        if (e.type() == window_event::drag_end) {
            if (dragging_) {
                dragging_ = false;
            }
        }

        if (e.type() == window_event::resize_start) {
            resizing_ = true;
            resize_start_ = io.MousePos - max_;
        }

        if (e.type() == window_event::resize_end) {
            if (resizing_) {
                resizing_ = false;
            }
        }

        last_mouse_pos_ = io.MousePos;
    }

    void window::render() {
        // shadow
        drawing::rect_shadow({ min_.x + 2, min_.y + 2 }, { max_.x - 2, max_.y - 2 }, IM_COL32(0, 0, 0, 255), 15.0f, {}, ImDrawCornerFlags_All, 4.0f);

        // top titlebar border
        drawing::rect_filled(min_, { max_.x, 12 }, color::border_light, 4.0f);

        // titlebar
        drawing::rect_filled(min_ + ImVec2(0, 1), ImVec2(max_.x, titlebar_height_), color::titlebar, 4.0f, 
            ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight);

        // bottom titlebar border
        drawing::rect_filled(min_ + ImVec2(0, titlebar_height_), ImVec2(max_.x, 1), color::border_dark);

        drawing::rect_filled(min_ + ImVec2(0, titlebar_height_ + 1), max_ - ImVec2(0, titlebar_height_ + 1), color::body_dark, 4.0f,
            ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight); 
    }
}
