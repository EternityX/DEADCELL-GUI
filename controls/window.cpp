#include "window.h"

#include <algorithm>

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"
#include "../wrapped/platform.h"

namespace deadcell::gui {
	window::window(const std::string_view unique_id) {
		unique_ids_.insert(std::pair(unique_id, this));
	}

	window::window(const std::string_view text, const std::string_view unique_id)
	    : text_(text) {
		unique_ids_.insert(std::pair(unique_id, this));
	}

    void window::center() {
		const auto &io = ImGui::GetIO();

		assert(io.DisplaySize.x > 0.0f); // center() should be called in the render loop. 
		assert(io.DisplaySize.y > 0.0f);

        pos_ = { (io.DisplaySize.x - size_.x) / 2.0f, (io.DisplaySize.y - size_.y) / 2.0f };
    }

    void window::event(base_event& e) {
		const auto& io = ImGui::GetIO();

		if (dragging_) {
			const auto new_pos = (input::get_mouse_pos() - interaction_mouse_pos_) + interaction_offset_;

			pos_.x = std::clamp(new_pos.x, 2.0f, io.DisplaySize.x - size_.x - 2.0f);
			pos_.y = std::clamp(new_pos.y, 2.0f, io.DisplaySize.y - size_.y - 2.0f);
		}

		if (resizing_) {
			const auto new_size = (input::get_mouse_pos() - interaction_mouse_pos_) + interaction_offset_;

			size_.x = std::clamp(new_size.x, min_size_.x, io.DisplaySize.x - pos_.x - 2.0f);
			size_.y = std::clamp(new_size.y, min_size_.y, io.DisplaySize.y - pos_.y - 2.0f);
		}

		if (e.type() == window_event::drag_start) {
			if (!dragging_) {
				dragging_ = true;
				interaction_mouse_pos_ = input::get_mouse_pos();
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
				interaction_mouse_pos_ = input::get_mouse_pos();
				interaction_offset_ = size_;
			}
		}

		if (e.type() == window_event::resize_end) {
			if (resizing_) {
				resizing_ = false;
			}
		}

		// Pass base events down to any potential children.
		if (e.type() == base_event::mouse_click || e.type() == base_event::mouse_down || e.type() == base_event::mouse_up
			|| e.type() == base_event::mouse_move || e.type() == base_event::mouse_hover) {
			e.ignore();
		}

		object::event(e);
	}

	void window::render() {
		if (size_.is_empty() || !visible_) {
			return;
		}

		// shadow
		drawing::rect_shadow(pos_ + 2.0f, size_ - 4.0f, color(0, 0, 0), 0.0f, 15.0f, 4.0f, drawing::draw_flags_shadow_cut_out_shape_background);

		// top titlebar border
		drawing::rect_filled(pos_, { size_.x, 12.0f }, colors::border_light, 4.0f);

		// titlebar
		drawing::rect_filled(point(pos_.x, pos_.y + 1.0f), point(size_.x, titlebar_height_), colors::titlebar, 4.0f, drawing::draw_flags_round_top);

		const auto title_text_size = drawing::measure_text(fonts::titlebar_font, 0.0f, 24.0f, text_.c_str());

		if (titlebar_height_ > title_text_size.y) {
			drawing::text({ pos_.x + 12.0f, pos_.y + titlebar_height_ / 2.0f - title_text_size.y / 2.0f }, colors::titlebar_text, fonts::titlebar_font, 0.0f, 0.0f, text_.c_str());

			/*constexpr float btn_radius = 7.0f;
			drawing::circle_filled({ pos_.x + size_.x - 24, pos_.y + titlebar_height_ / 2 - btn_radius / 2 + btn_radius - 2 }, btn_radius, colors::red, static_cast<int>(btn_radius * 3));

			if (!desktop_window_) {
				drawing::circle_filled({ pos_.x + size_.x - 24 - btn_radius * 2 - 8, pos_.y + titlebar_height_ / 2 - btn_radius / 2 + btn_radius - 2 }, btn_radius, colors::yellow, static_cast<int>(btn_radius * 3));
			}*/
		}

		// bottom titlebar border
		drawing::rect_filled(point(pos_.x, pos_.y + titlebar_height_), point(size_.x, 1.0f), colors::border_dark);

		// body
		dragging_alpha_ = platform::fade(dragging_alpha_, dragging_ ? 1.0f : 0.0f, 0.111f);

		const auto body_dark_color = colors::body_dark.adjust_alpha(255 - static_cast<int>(82.0f * dragging_alpha_));

		drawing::rect_filled(point(pos_.x, pos_.y + titlebar_height_ + 1.0f), size_ - point(0.0f, titlebar_height_ + 1.0f), body_dark_color, 4.0f, drawing::draw_flags_round_bottom);
	}
}
