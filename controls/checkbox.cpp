#include "checkbox.h"

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"
#include "../wrapped/platform.h"

#include "../thirdparty/material_icons.h"

deadcell::gui::checkbox::checkbox(const std::string_view text, std::string_view unique_id, bool *var, std::function<void()> callback)
    : text_(text), var_(var), func_(std::move(callback)) {
    assert(!unique_id.empty());
    unique_ids_.insert(std::pair(unique_id, this));
}

void deadcell::gui::checkbox::event(base_event &e) {
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
            hovered_ = input::is_mouse_in_bounds(pos_, size_);
        }
    }

    object::event(e);
}

void deadcell::gui::checkbox::layout(layout_item &overlay, layout_item &parent) {
}

void deadcell::gui::checkbox::render() {
    if (!visible_) {
        return;
    }

    checkmark_clip_width_ = platform::fade(checkmark_clip_width_, size_.x, 0.096f, 0.1f, 0.0f, size_.x);

    // Body
    if (*var_) {
        drawing::rect_filled(pos_, size_, colors::checkbox_checked_body, 1.0f);

        drawing::push_clip_rect(pos_, { checkmark_clip_width_, size_.y });
        {
            drawing::text(pos_, colors::body_dark, fonts::icons_font, 0.0f, 16.0f, ICON_MD_CHECK);
        }
        drawing::pop_clip_rect();
    }
    else {
        // Hacky fix to draw the outline properly.
        drawing::get_draw_list()->Flags &= ~drawing::draw_list_flags_anti_aliased_lines;
        drawing::rect(pos_ + 1.0f, size_ - 2.0f, colors::checkbox_unchecked_body, 0.0f, drawing::draw_flags_none, 2.0f);
        drawing::get_draw_list()->Flags |= drawing::draw_list_flags_anti_aliased_lines;

        // Reproduce the corner anti aliasing effect.
        const color corner_color = colors::checkbox_unchecked_body.adjust_alpha(255 / 2);

        drawing::rect_filled(pos_, { 1.0f, 1.0f }, corner_color); // Top left
        drawing::rect_filled({ pos_.x + size_.x - 1.0f, pos_.y }, { 1.0f, 1.0f }, corner_color); // Top Right
        drawing::rect_filled({ pos_.x, pos_.y + size_.y - 1.0f }, { 1.0f, 1.0f }, corner_color); // Bottom left
        drawing::rect_filled(pos_ + size_ - point{ 1.0f, 1.0f }, { 1.0f, 1.0f }, corner_color); // Bottom right
    }
}
