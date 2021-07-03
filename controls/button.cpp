#include "button.h"

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"

namespace deadcell::gui {
    button::button(const std::string_view text, std::string_view unique_id, std::function<void()> callback)
        : text_(text), func_(std::move(callback)) {
        unique_ids_.insert(std::pair(unique_id, this));
    }

    button::button(const std::string_view text, std::string_view unique_id, const point size, std::function<void()> callback)
        : text_(text), size_(size), func_(std::move(callback)) {
        unique_ids_.insert(std::pair(unique_id, this));
    }

    bool button::is_visible() const {
		return visible_;
    }

    void button::event(base_event &e) {
        if (e.type() == base_event::mouse_click) {
            if (hovered_) {
                mouse_clicked_ = true;
            }
        }

        object::event(e);
    }

    void button::layout(layout_item &overlay, layout_item &parent) {
        object::layout(overlay, parent);

        const point title_text_size = drawing::measure_text(fonts::titlebar_font, 0.0f, 16.0f, text_.c_str());
    }

    void button::render() {
        if (size_.is_empty() || !visible_) {
            return;
        }

        hovered_ = input::is_in_bounds(pos_, size_);

        // shadow
        drawing::rect_shadow(pos_ + point(5, size_.y - 5), point(size_.x - 10, 5), colors::shadow, 0.0f, 12.0f, 4.0f, drawing::draw_flags_shadow_cut_out_shape_background);
        
        // body
        drawing::rect_filled(pos_, size_, colors::button_default, 4.0f);
    }
}
