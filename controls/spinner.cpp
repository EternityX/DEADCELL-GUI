#include "spinner.h"

#include "../wrapped/drawing.h"

#include "../vendor/imgui/imgui_internal.h"
#include "../vendor/cubic_bezier.h"

namespace deadcell::gui {
    constexpr static auto lerp(const float x0, const float x1) {
        return [=](const float t) {
            return (1.0f - t) * x0 + t * x1;
        };
    }

    static float lerp(const float x0, const float x1, const float t) {
        return lerp(x0, x1)(t);
    }

    static auto interval(float t0, float t1, const std::function<float(float)> &tween = lerp(0.0, 1.0)) {
        return [=](const float t) {
            return t < t0 ? 0.0f : t > t1 ? 1.0f : tween((t - t0) / (t1 - t0));
        };
    }

    static cubic_bezier fast_out_slow_in(0.4, 0.0, 0.2, 1.0);
    static float bezier(const float t) {
        return static_cast<float>(fast_out_slow_in.solve(t));
    }

    void spinner::event(base_event &e) {

    }

    void spinner::layout(layout_item &overlay, layout_item &parent) {

    }

    void spinner::render() {
        ImGuiContext &ctx = *GImGui;

        const auto center = point(pos_.x + radius_, pos_.y + radius_ + 4.0f);

        constexpr float start_angle = -IM_PI / 2.0f; // Start at the top
        constexpr int num_detents = 5;               // How many rotations we want before a repeat
        constexpr int skip_detents = 3;              // How many steps we skip each rotation
        constexpr float period = 5.0f;               // In seconds

        const float t = std::fmod(static_cast<float>(ctx.Time), period) / period; // Map period into [0, 1]

        // Tweening functions for each part of the spinner
        auto stroke_head_tween = [](float t) {
            t = sawtooth<num_detents>(t);
            return interval(0.0f, 0.5f, bezier)(t);
        };

        auto stroke_tail_tween = [](float t) {
            t = sawtooth<num_detents>(t);
            return interval(0.5f, 1.0f, bezier)(t);
        };

        auto step_tween = [=](float t) {
            return std::floor(lerp(0.0, static_cast<float>(num_detents), t));
        };

        const auto rotation_tween = sawtooth<num_detents>;

        const float head_value = stroke_head_tween(t);
        const float tail_value = stroke_tail_tween(t);
        const float step_value = step_tween(t);
        const float rotation_value = rotation_tween(t);

        constexpr float min_arc = 40.0f / 360.0f * 2.0f * IM_PI;
        constexpr float max_arc = 270.0f / 360.0f * 2.0f * IM_PI;
        constexpr float step_offset = skip_detents * 2.0f * IM_PI / num_detents;
        const float rotation_compensation = std::fmodf(4.0f * IM_PI - step_offset - max_arc, 2.0f * IM_PI);

        const float a_min = start_angle + tail_value * max_arc + rotation_value * rotation_compensation - step_value * step_offset;
        const float a_max = a_min + (head_value - tail_value) * max_arc + min_arc;

        drawing::get_draw_list()->PathClear();

        constexpr int num_segments = 48;
        for (int i = 0; i < num_segments; i++) {
            const float a = a_min + static_cast<float>(i) / static_cast<float>(num_segments) * (a_max - a_min);
            drawing::get_draw_list()->PathLineTo(ImVec2(center.x + std::cos(a) * radius_, center.y + std::sin(a) * radius_));
        }

        drawing::get_draw_list()->PathStroke(colors::pink, 0, thickness_);
    }
}
