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

        if (dragging_) {
            const auto delta = io.MousePos - interaction_mouse_pos_;
            const auto new_pos = delta + interaction_offset_;

            pos_.x = std::clamp(new_pos.x, 2.0f, io.DisplaySize.x - size_.x - 2.0f);
            pos_.y = std::clamp(new_pos.y, 2.0f, io.DisplaySize.y - size_.y - 2.0f);
        }

        if (resizing_) {
            const auto delta = io.MousePos - interaction_mouse_pos_;
            const auto new_size = delta + interaction_offset_;

            size_.x = std::clamp(new_size.x, min_size_.x, io.DisplaySize.x - pos_.x - 2.0f);
            size_.y = std::clamp(new_size.y, min_size_.y, io.DisplaySize.y - pos_.y - 2.0f);
        }

        if (e.type() == window_event::drag_start) {
            if (!dragging_) {
                dragging_ = true;
                interaction_mouse_pos_ = io.MousePos;
                interaction_offset_ = pos_;
            }
        }

        if (e.type() == window_event::drag_end) {
            if (dragging_) {
                dragging_ = false;
            }
        }

        if (e.type() == window_event::resize_start) {
            if (!resizing_) {
                resizing_ = true;
                interaction_mouse_pos_ = io.MousePos;
                interaction_offset_ = size_;
            }
        }

        if (e.type() == window_event::resize_end) {
            if (resizing_) {
                resizing_ = false;
            }
        }
    }

    void window::render() {
        // shadow
        drawing::rect_shadow(pos_ + ImVec2(2, 2), size_ - ImVec2(4, 4), IM_COL32(0, 0, 0, 255), 15.0f, {}, ImDrawFlags_None | ImDrawFlags_ShadowCutOutShapeBackground, 4.0f);

        // top titlebar border
        drawing::rect_filled(pos_, { size_.x, 12 }, color::border_light, 4.0f);

        // titlebar
        drawing::rect_filled(pos_ + ImVec2(0, 1), ImVec2(size_.x, titlebar_height_), color::titlebar, 4.0f,  ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight);

        const auto titlebar_text = "DEADCELL";
        const auto title_text_size = drawing::measure_text(font::titlebar_font, 0.0f, 24.0f, titlebar_text);

        if (titlebar_height_ > title_text_size.y) {
            drawing::text({ pos_.x + 15, pos_.y + titlebar_height_ / 2 - title_text_size.y / 2 }, color::titlebar_text, font::titlebar_font, 0.0f, 0.0f, titlebar_text);
        }

        // bottom titlebar border
        drawing::rect_filled(pos_ + ImVec2(0, titlebar_height_), ImVec2(size_.x, 1), color::border_dark);

        // body
        dragging_alpha_ = drawing::alpha_fade(dragging_alpha_, dragging_ ? 1.0f : 0.0f, 0.111f);
        const auto body_dark_color = color::body_dark - IM_COL32(0, 0, 0, std::clamp(static_cast<int>(82.0f * dragging_alpha_), 0, 255));

        drawing::rect_filled(pos_ + ImVec2(0, titlebar_height_ + 1), size_ - ImVec2(0, titlebar_height_ + 1), body_dark_color, 4.0f, ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight);     
    }
}
