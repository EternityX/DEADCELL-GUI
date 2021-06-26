#pragma once

#include "../controls/object.h"

namespace deadcell::gui {
    class window : public object {
    private:
        bool visible_ = true;
        bool resizeable_ = true;
        bool dragging_ = false;
        bool resizing_ = false;

        ImVec2 pos_;
        ImVec2 size_;
        ImVec2 min_size_ = { 250, 250 };

        ImVec2 interaction_mouse_pos_;
        ImVec2 interaction_offset_;

        float titlebar_height_ = 50.0f;
        float dragging_alpha_ = 1.0f;

    protected:
        std::string unique_id_;

    public:
        window(std::string_view unique_id);

        void set_position_size(const ImVec2 pos, const ImVec2 size) {
            pos_ = pos;
            size_ = size;
        }

        void set_position(const ImVec2 pos) {
            pos_ = pos;
        }

        void set_size(const ImVec2 size) {
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

        void set_min_size(const ImVec2 size) {
            min_size_ = size;
        }

        ImVec2 get_postition() const {
            return pos_;
        }

        ImVec2 get_size() const {
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

        std::string get_class_name() override { return "window()"; }
    };
}