/*
 * Copyright (c) 2021, EternityX <jeramie@protonmail.com>
 *
 * SPDX License Identifier: BSD-3-Clause
 */

#pragma once

#include <functional>

#include "../controls/object.h"

namespace deadcell::gui {
    template <typename T>
    class slider : public object {
    private:
        std::string text_;

        bool enabled_ = true;
        bool visible_ = true;

        point pos_;
        point size_;

        T *var_;
        T value_min_;
        T value_max_;

        std::string format_;
        std::function<std::string(T)> format_func_;

    protected:
        std::string unique_id_;

    public:
        slider(std::string_view text, std::string_view unique_id, T *var, T value_min, T value_max, std::string_view format);

        slider(std::string_view text, std::string_view unique_id, T *var, T value_min, T value_max, std::function<std::string(T)> format);

        void set_position_size(const point &pos, const point &size) {
            pos_ = pos;
            size_ = size;
        }

        void set_position(const point pos) {
            pos_ = pos;
        }

        void set_size(const point &size) {
            size_ = size;
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

        std::string get_class_name() override { return "slider"; }
    };
}