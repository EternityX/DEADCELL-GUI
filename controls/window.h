#pragma once

#include "../controls/object.h"

namespace deadcell::gui {
    class window : public object {
    private:
        bool visible_ = true;
        bool resizeable_ = true;

        ImVec2 min_;
        ImVec2 max_;
        ImVec2 last_mouse_pos_;

        int titlebar_height_ = 50;
        ImVec2 min_size_ = { 250, 250 };

        bool   dragging_ = false;
        ImVec2 drag_start_;

        bool   resizing_ = false;
        ImVec2 resize_start_;
    protected:
        std::string unique_id_;

    public:
        window(std::string_view unique_id);

        void set_min_max(const ImVec2 min, const ImVec2 max) {
            min_ = min;
            max_ = max;
        }

        void set_min(const ImVec2 min) {
            min_ = min;
        }

        void set_max(const ImVec2 max) {
            max_ = max;
        }

        void set_position(const ImVec2 pos) {
            min_ = pos;
        }

        void set_size(const ImVec2 size) {
            max_ = min_ + size;
        }

        void set_drag_zone(const ImVec2 size) {
            
        }

        ImVec2 get_min() const {
            return min_;
        }

        ImVec2 get_max() const {
            return max_;
        }

        ImVec2 get_size() const {
            return max_ + min_;
        }

        int get_titlebar_height() const {
            return titlebar_height_;
        }

        bool is_visible() const {
            return visible_;
        }

        bool is_resizable() const {
            return resizeable_;
        }

        void event(const base_event &e) override;
        void render() override;
        std::string get_class_name() override { return "window()"; }
    };
}