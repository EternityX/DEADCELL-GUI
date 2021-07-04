#include "button.h"

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"
#include "../wrapped/platform.h"

namespace deadcell::gui {
    button::button(const std::string_view text, std::string_view unique_id, std::function<void()> callback)
        : text_(text), func_(std::move(callback)) {
        unique_ids_.insert(std::pair(unique_id, this));
    }

    button::button(const std::string_view text, std::string_view unique_id, const point size, std::function<void()> callback)
        : text_(text), size_(size), func_(std::move(callback)) {
        unique_ids_.insert(std::pair(unique_id, this));
    }

    void button::event(base_event &e) {
        if (e.type() == base_event::mouse_click) {
            if (hovered_ && visible_ && enabled_) {
                click_circle_size_ = 30.0f;
                click_circle_alpha_ = 0.0f;
                click_circle_start_ = input::get_mouse_pos();
            }
        }

        if (e.type() == base_event::mouse_down) {
            if (hovered_ && visible_ && enabled_) {
                mouse_clicked_ = true;
            }
        }

        if (e.type() == base_event::mouse_up) {         
            if (hovered_ && visible_ && enabled_) {
                func_();
                mouse_clicked_ = false;
            }
        }

        if (e.type() == base_event::hover) {
            if (visible_ && enabled_) {
                hovered_ = input::is_in_bounds(pos_, size_);
            }
        }

        object::event(e);
    }

    void button::layout(layout_item &overlay, layout_item &parent) {
        object::layout(overlay, parent);

        const point title_text_size = drawing::measure_text(fonts::button_font, 0.0f, 16.0f, text_.c_str());
    }

    void button::render() {
        if (size_.is_empty() || !visible_) {
            return;
        }

        hover_alpha_ = platform::fade(hover_alpha_, hovered_ ? 1.0f : 0.0f);
        shadow_thickness_ = platform::fade(shadow_thickness_, hovered_ ? 48.0f : 12.0f, 0.2f, 0.1f, 12.0f, 48.0f);

        click_circle_alpha_ = platform::fade(click_circle_alpha_, 1.0f, 0.2f, 0.1f, 0.9f, 1.0f);
        click_circle_size_ = platform::fade(click_circle_size_, 100.0f, 0.2f, 0.2f, 10.0f, 200.0f);

        // shadow
        if (enabled_) {
            drawing::rect_shadow(pos_ + point(5, size_.y - 0), point(size_.x - 10, 0), colors::shadow, 0.0f, shadow_thickness_, 4.0f, drawing::draw_flags_shadow_cut_out_shape_background);
        }

        // body
        const color circle_color = colors::white.adjust_alpha(255 - static_cast<int>(255.0f * click_circle_alpha_));
        color body_color, text_color;
        
        if (enabled_) {
            body_color = colors::button_body.adjust_alpha(255 - static_cast<int>(82.0f * hover_alpha_));
            text_color = colors::button_text;
        }
        else {
            body_color = colors::button_body_disabled;
            text_color = colors::button_text_disabled;
        }

        drawing::rect_filled(pos_, size_, body_color, 4.0f);
        
        drawing::push_clip_rect(pos_, size_);
        {
            drawing::fill_circle({ click_circle_start_.x, click_circle_start_.y }, click_circle_size_, circle_color, 500);

            const auto text_size = drawing::measure_text(fonts::button_font, auto_size_ ? size_.x - 30.0f : 0.0f, 16.0f, text_.c_str());
            static bool did_resize = false;

            // resize body height to fit text
            if (auto_size_) {
                if ((text_size.y > size_.x || text_size.y < size_.x) && text_size.y <= max_size_.y) {
                    did_resize = true;

                    size_.y = text_size.y + 30.0f;
                }
            }
            else {
                did_resize = false;
            }

            if (hovered_ && visible_ && enabled_) {
                platform::set_cursor(platform::cursor_hand);
            }

            drawing::text({ pos_.x + size_.x / 2 - text_size.x / 2, pos_.y + size_.y / 2 - text_size.y / 2 }, text_color, fonts::button_font, did_resize ? size_.x - 30 : 0.0f, 16.0f, text_.c_str());
        }
        drawing::pop_clip_rect();      
    }
}
