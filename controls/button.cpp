#include "button.h"

#include <iostream>

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"
#include "../wrapped/platform.h"
 
namespace deadcell::gui {
    button::button(const std::string_view text, std::string_view unique_id, std::function<void()> callback)
        : text_(text), func_(std::move(callback)) {
        assert(!unique_id.empty());
        unique_ids_.insert(std::pair(unique_id, this));
    }

    button::button(const std::string_view text, std::string_view unique_id, const point size, std::function<void()> callback)
        : text_(text), size_(size), func_(std::move(callback)) {
        assert(!unique_id.empty());
        unique_ids_.insert(std::pair(unique_id, this));
    }

    void button::event(base_event &e) {
        const bool valid = enabled_ && visible_ && hovered_;

        if (e.type() == base_event::mouse_click) {
            if (valid) {
                mouse_clicked_ = true;
            }
        }

        if (e.type() == base_event::mouse_up) {
            if (valid && mouse_clicked_) {
                mouse_clicked_ = false;
                click_circle_ = { input::get_mouse_pos(), 0.0f, 30.0f };

                func_();
            }
        }

        if (e.type() == base_event::mouse_hover) {
            if (visible_ && enabled_) {
                hovered_ = input::is_mouse_in_bounds(pos_, size_);
            }
        }

        object::event(e);
    }

    void button::layout(layout_item &overlay, layout_item &parent) {
        object::layout(overlay, parent);
    }

    void button::render() {
        if (size_.is_empty() || !visible_) {
            return;
        }

        hover_alpha_ = platform::fade(hover_alpha_, hovered_ ? 1.0f : 0.0f);
        shadow_thickness_ = platform::fade(shadow_thickness_, hovered_ ? 48.0f : 12.0f, 0.2f, 0.1f, 12.0f, 48.0f);

        click_circle_.alpha = platform::fade(click_circle_.alpha, 1.0f, 0.2f, 0.1f, 0.9f, 1.0f);
        click_circle_.size = platform::fade(click_circle_.size, 100.0f, 0.2f, 0.2f, 10.0f, 200.0f);

        // Shadow
        if (enabled_) {
            drawing::rect_shadow(pos_ + point(5.0f, size_.y - 0.0f), point(size_.x - 10.0f, 0.0f), 
                colors::shadow, 0.0f, shadow_thickness_, 4.0f, drawing::draw_flags_shadow_cut_out_shape_background);
        }

        // Body
        const color circle_color = colors::white.adjust_alpha(255 - static_cast<int>(255.0f * click_circle_.alpha));
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
            drawing::circle_filled({ click_circle_.start.x, click_circle_.start.y }, click_circle_.size, circle_color, 250);

            const auto text_size = drawing::measure_text(fonts::button_font, auto_size_ ? size_.x - 30.0f : 0.0f, 16.0f, text_.c_str());
            bool did_resize = false;

            // Resize body height to fit text
            if (auto_size_) {
                if ((text_size.y > size_.x || text_size.y < size_.x) && text_size.y <= max_size_.y) {
                    did_resize = true;

                    size_.y = text_size.y + 30.0f;
                }
            }

            drawing::text({ pos_.x + size_.x / 2.0f - text_size.x / 2.0f, pos_.y + size_.y / 2.0f - text_size.y / 2.0f }, 
                text_color, fonts::button_font, did_resize ? size_.x - 30.0f : 0.0f, 16.0f, text_.c_str());
        }
        drawing::pop_clip_rect();

        if (hovered_ && visible_ && enabled_) {
            platform::set_cursor(platform::cursor_hand);
        }
    }
}
