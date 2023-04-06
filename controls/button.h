/*
 * Copyright (c) 2021, EternityX <jeramie@protonmail.com>
 *
 * SPDX License Identifier: BSD-3-Clause
 */

#pragma once

#include <functional>

#include "../controls/object.h"

namespace deadcell::gui {
    class button : public object {
    private:
        std::string text_;

        bool enabled_ = true;
        bool visible_ = true;
        bool hovered_ = false;
        bool auto_size_ = false;
        bool mouse_clicked_ = false;

        float hover_alpha_ = 1.0f;
        float shadow_thickness_ = 12.0f;

        struct click_circle {
            point start;
            float alpha = 1.0f;
            float size = 0.0f;
        } click_circle_;

        point pos_;
        point size_ = { 150, 35 };
        point max_size_ = { 250, 250 };

        std::function<void()> func_;

    protected:
        std::string unique_id_;

    public:
        button(std::string_view text, std::string_view unique_id, std::function<void()> callback);
        button(std::string_view text, std::string_view unique_id, point size, std::function<void()> callback);

        void set_position_size(const point &pos, const point &size) {
            pos_ = pos;
            size_ = size;
        }

        void set_position(const point &pos) {
            pos_ = pos;
        }

        void set_size(const point &size) {
            size_ = size;
        }

        void set_max_size(const point &max_size) {
            max_size_ = max_size;
        }

        void set_visible(const bool visible) {
            visible_ = visible;
        }

        void set_auto_size(const bool auto_size) {
            auto_size_ = auto_size;
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

        bool is_auto_size() const {
            return auto_size_;
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

        std::string get_class_name() override { return "button"; }
    };
}