/*
 * Copyright (c) 2021, EternityX <eternity@enevade.org>
 *
 * SPDX License Identifier: BSD-3-Clause
 */

#pragma once

#include <functional>

#include "../controls/object.h"

namespace deadcell::gui {
    class checkbox : public object {
    private:
        std::string text_;

        bool enabled_ = true;
        bool visible_ = true;
        bool hovered_ = false;
        bool mouse_clicked_ = false;

        float hover_alpha_ = 0.0f;
        float body_click_alpha_ = 1.0f;
        float checkmark_clip_width_ = 0.0f;

        point pos_;
        point size_ { 16, 16 };

        bool *var_;
        std::function<void()> func_;

    protected:
        std::string unique_id_;

    public:
        checkbox(std::string_view text, std::string_view unique_id, bool *var, std::function<void()> callback = nullptr);

        void set_position_size(const point &pos, const point &size) {
            pos_ = pos;
            size_ = size;
        }

        void set_position(const point &pos) {
            pos_ = pos;
        }

        void set_visible(const bool visible) {
            visible_ = visible;
        }

        void set_enabled(const bool enabled) {
            enabled_ = enabled;
        }

        void set_text(const std::string_view text) {
            text_ = text;
        }

        point get_position() const {
            return pos_;
        }

        point get_size() const {
            return size_;
        }

        bool is_visible() const {
            return visible_;
        }

        void show() {
            visible_ = true;
        }

        void hide() {
            visible_ = false;
        }

        void enable() {
            enabled_ = true;
        }

        void disable() {
            enabled_ = false;
        }

        void event(base_event &e) override;
        void layout(layout_item &overlay, layout_item &parent) override;
        void render() override;

        std::string get_class_name() override { return "checkbox"; }
    };
}