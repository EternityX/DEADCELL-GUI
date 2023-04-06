/*
 * Copyright (c) 2021, EternityX <jeramie@protonmail.com>
 *
 * SPDX License Identifier: BSD-3-Clause
 */

#pragma once

#include <functional>

#include "../controls/object.h"

namespace deadcell::gui {
    class spinner : public object {
    private:
        std::string text_;

        bool enabled_ = true;
        bool visible_ = true;

        point pos_;

        color color_ = colors::pink;
        float radius_ = 25.0f;
        float thickness_ = 5.0f;

        template <int T>
        static float sawtooth(const float t) {
            return std::fmod(static_cast<float>(T) * t, 1.0f);
        }

    protected:
        std::string unique_id_;

    public:
        spinner(std::string_view unique_id);

        spinner(std::string_view unique_id, float radius);

        void set_position_radius(const point pos, const float radius) {
            pos_ = pos;
            radius_ = radius;
        }

        void set_position(const point pos) {
            pos_ = pos;
        }

        void set_radius(const float radius) {
            radius_ = radius;
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

        void set_thickness(const float thickness) {
            thickness_ = thickness;
        }

        void set_color(const color col) {
            color_ = col;
        }

        point get_position() const {
            return pos_;
        }

        point get_radius() const {
            return radius_;
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

        std::string get_class_name() override { return "spinner"; }
    };
}