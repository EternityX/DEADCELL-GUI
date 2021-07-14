#include "checkbox.h"

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"
#include "../wrapped/platform.h"

#include "../vendor/material_icons.h"

namespace deadcell::gui {
    checkbox::checkbox(const std::string_view text, std::string_view unique_id, bool *var, std::function<void()> callback)
        : text_(text), var_(var), func_(std::move(callback)) {
        assert(!unique_id.empty());
        assert(var);

        unique_ids_.insert(std::pair(unique_id, this));
    }

    void checkbox::event(base_event &e) {
        const bool valid = hovered_ && visible_ && enabled_;

        if (e.type() == base_event::mouse_click) {
            if (valid) {
                mouse_clicked_ = true;
            }
        }

        if (e.type() == base_event::mouse_up) {
            if (valid && mouse_clicked_) {
                mouse_clicked_ = false;
                checkmark_clip_width_ = 0.0f;

                func_();
            }
        }

        if (e.type() == base_event::mouse_hover) {
            if (visible_ && enabled_) {
                const auto text_size = drawing::measure_text(fonts::checkbox_font, 0.0f, 16.0f, text_.c_str());

                hovered_ = input::is_mouse_in_bounds(pos_, { size_.x + text_size.x + 8.0f, size_.y });
            }
        }

        object::event(e);
    }

    void checkbox::layout(layout_item &overlay, layout_item &parent) {
    }

    void checkbox::render() {
        if (!visible_) {
            return;
        }

        hover_alpha_ = platform::fade(hover_alpha_, hovered_ ? 1.0f : 0.0f);
        body_click_alpha_ = platform::fade(body_click_alpha_, *var_ ? 0.0f : 1.0f, 0.08f, 0.08f, 0.0f);

        checkmark_clip_width_ = platform::fade(checkmark_clip_width_, size_.x, 0.076f, 0.11f, 0.0f, size_.x);

        color check_body_color, uncheck_body_color, text_color;

        if (enabled_) {
            check_body_color = colors::green;
            uncheck_body_color = colors::checkbox_background;
            text_color = colors::checkbox_text;
        }
        else {
            check_body_color = colors::green;
            uncheck_body_color = colors::checkbox_background;
            text_color = colors::checkbox_text_disabled;
        }

        // Body
        if (static_cast<int>(255.0f * body_click_alpha_) > 0) {
            // Hacky fix to draw the outline properly.
            drawing::get_draw_list()->Flags &= ~drawing::draw_list_flags_anti_aliased_lines;
            drawing::rect(pos_ + 1.0f, size_ - 2.0f, uncheck_body_color, 0.0f, drawing::draw_flags_none, 2.0f);
            //drawing::rect_filled(pos_, size_, uncheck_body_color, 2.0f, drawing::draw_flags_none);
            drawing::get_draw_list()->Flags |= drawing::draw_list_flags_anti_aliased_lines;

            const color corner_color = uncheck_body_color.adjust_alpha(255 / 2);

            // Reproduce the corner anti aliasing effect.
            drawing::rect_filled(pos_, { 1.0f, 1.0f }, corner_color); // Top left
            drawing::rect_filled({ pos_.x + size_.x - 1.0f, pos_.y }, { 1.0f, 1.0f }, corner_color); // Top Right
            drawing::rect_filled({ pos_.x, pos_.y + size_.y - 1.0f }, { 1.0f, 1.0f }, corner_color); // Bottom left
            drawing::rect_filled(pos_ + size_ - point{ 1.0f, 1.0f }, { 1.0f, 1.0f }, corner_color); // Bottom right
        }

        drawing::rect_filled(pos_, size_, check_body_color.adjust_alpha(255 - static_cast<int>(255.0f * body_click_alpha_)), 1.0f);

        // Checkmark
        if (*var_) {
            drawing::push_clip_rect(pos_, { checkmark_clip_width_, size_.y });
        }
        else {
            drawing::push_clip_rect({ pos_.x - checkmark_clip_width_, pos_.y }, size_);
        }

        drawing::text(pos_ + point{ 0.0f, 1.0f }, colors::body_dark, fonts::icons_font, 0.0f, 15.0f, ICON_MD_CHECK);

        drawing::pop_clip_rect();

        // Text
        const auto text_size = drawing::measure_text(fonts::checkbox_font, 0.0f, 15.0f, text_.c_str());

        drawing::text({ pos_.x + size_.x + 6.0f, pos_.y + size_.y / 2.0f - text_size.y / 2.0f },
            text_color, fonts::checkbox_font, 0.0f, 16.0f, text_.c_str());

        if (hovered_ && visible_ && enabled_) {
            platform::set_cursor(platform::cursor_hand);
        }
    }
}