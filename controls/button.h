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

        point click_circle_start_;
        float click_circle_alpha_ = 1.0f;
        float click_circle_size_ = 0.0f;

        point pos_;
        point size_;
        point max_size_ = { 1000, 1000 };

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

        void event(base_event &e) override;
        void layout(layout_item &overlay, layout_item &parent) override;
        void render() override;

        std::string get_class_name() override { return "button"; }
    };
}