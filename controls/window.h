#pragma once

#include "../controls/object.h"

namespace deadcell::gui {
    class window : public object {
    private:
        std::string text_;

        bool visible_ = true;
        bool resizeable_ = true;
        bool dragging_ = false;
        bool resizing_ = false;

        point pos_;
        point size_;
        point min_size_ = { 250, 250 };

        point interaction_mouse_pos_;
        point interaction_offset_;

        float titlebar_height_ = 50.0f;
        float dragging_alpha_ = 1.0f;

    protected:
        std::string unique_id_;

    public:
        window(std::string_view unique_id);
        window(std::string_view text, std::string_view unique_id);

        void set_position_size(const point& pos, const point& size) {
            pos_ = pos;
            size_ = size;
        }

        void set_position(const point& pos) {
            pos_ = pos;
        }

        void set_size(const point& size) {
            size_ = size;
        }

        void set_visible(const bool visible) {
            visible_ = visible;
        }

        void set_resizeable(const bool resizeable) {
            resizeable_ = resizeable;
        }

        void set_titlebar_height(const float titlebar_height) {
            titlebar_height_ = titlebar_height;
        }

        void set_min_size(const point& size) {
            min_size_ = size;
        }

        point get_position() const {
            return pos_;
        }

        point get_size() const {
            return size_;
        }

        float get_titlebar_height() const {
            return titlebar_height_;
        }

        bool is_visible() const {
            return visible_;
        }

        bool is_resizable() const {
            return resizeable_;
        }

        void event(base_event &e) override;
        void render() override;

        std::string get_class_name() override { return "window"; }
    };
}