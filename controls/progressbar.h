/*
 * Copyright (c) 2021, EternityX <eternity@enevade.org>
 *
 * SPDX License Identifier: BSD-3-Clause
 */

#pragma once

#include <algorithm>
#include <functional>

#include "../controls/object.h"

namespace deadcell::gui {
    template <typename T = int>
    class progressbar : public object {
    private:
        std::string text_;

        bool enabled_ = true;
        bool visible_ = true;

        point pos_ = { 200.0f, 6.0f };
        point size_;

        T progress_ = 0;
        T progress_min_ = 0;
        T progress_max_ = 100;

        std::function<void()> completed_func_;
        std::function<void()> tick_func_;

    protected:
        std::string unique_id_;

    public:
        progressbar(const std::string_view text, std::string_view unique_id,
            std::function<void()> completed_callback, std::function<void()> tick_callback = nullptr)
            : text_(text), completed_func_(std::move(completed_callback)), tick_func_(std::move(tick_callback)) {

            assert(!unique_id.empty());
            unique_ids_.insert(std::pair(unique_id, this));
        }

        progressbar(const std::string_view text, std::string_view unique_id, const float width,
            std::function<void()> completed_callback, std::function<void()> tick_callback = nullptr)
            : text_(text), completed_func_(std::move(completed_callback)), tick_func_(std::move(tick_callback)) {

            assert(!unique_id.empty());
            unique_ids_.insert(std::pair(unique_id, this));
            size_ = { width, 6.0f };
        }

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

        void set_visible(const bool visible) {
            visible_ = visible;
        }

        void set_enabled(const bool enabled) {
            enabled_ = enabled;
        }

        void set_text(const std::string_view text) {
            text_ = text;
        }

        void set_progress(const T progress) {
            progress_ = progress;
            run_callbacks();
        }

        void set_progress_min(const T progress_min) {
            if (progress_min <= progress_min_) {
                progress_min_ = progress_min;
            }
        }

        void set_progress_max(const T progress_max) {
            if (progress_max >= progress_max_) {
                progress_max_ = progress_max;
            }
        }

        void increment_progress(const T increment) {
            progress_ = std::clamp(progress_ += increment, progress_min_, progress_max_);
            run_callbacks();
        }

        void decrement_progress(const T decrement) {
            progress_ = std::clamp(progress_ -= decrement, progress_min_, progress_max_);
            run_callbacks();
        }

        void run_callbacks() {
            if (tick_func_) {
                tick_func_();
            }

            if (progress_ >= progress_max_) {
                completed_func_();
            }
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

        T get_progress() const {
            return progress_;
        }

        void event(base_event &e) override;
        void layout(layout_item &overlay, layout_item &parent) override;
        void render() override;

        std::string get_class_name() override { return "progressbar"; }
    };
}