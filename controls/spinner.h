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

        float radius_ = 25.0f;
        float thickness_ = 5.0f;

        template <int T>
        static float sawtooth(const float t) {
            return std::fmodf(static_cast<float>(T) * t, 1.0f);
        }

    protected:
        std::string unique_id_;

    public:
        spinner(std::string_view unique_id) {
            assert(!unique_id.empty());
            unique_ids_.insert(std::pair(unique_id, this));
        }

        spinner(std::string_view unique_id, const float radius)
            : radius_(radius) {
            assert(!unique_id.empty());
            unique_ids_.insert(std::pair(unique_id, this));
        }

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