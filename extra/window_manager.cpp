#include "../instance.h"
#include "window_manager.h"

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"

#include <deque>

namespace deadcell::gui {
    void window_manager::add_window(const window_ptr &win) {
        const bool is_first_window = windows_.empty();

        windows_.push_back(win);

        if (is_first_window) {
            set_active_window(win);
        }
    }

    void window_manager::remove_window(const window_ptr& win) {
        if (const auto it = std::ranges::find_if(windows_, [&win](const window_ptr &ptr) {
            return ptr.get() == win.get();
        }); it != windows_.end()) {
            windows_.erase(it);
        }
    }

    void window_manager::set_active_window(const window_ptr &win) {
        if (win == active_window_) {
            return;
        }

        active_window_ = win;
    }

    void window_manager::move_to_front(const window_ptr &win, const bool make_active) {
        remove_window(win);
        add_window(win);

        if (make_active) {
            set_active_window(win);
        }
    }

    std::shared_ptr<window> window_manager::get_window_under_cursor() {
        const auto &io = ImGui::GetIO();

        std::deque<window_ptr> windows;

        for (auto &win : windows_) {
            if (input::mouse_in_bounds(win->get_min(), win->get_size())) {
                if (win == active_window_) {
                    return win;
                }

                windows.push_back(win);
            }
        }

        if (windows.size() > 1) {
            return windows.back();
        }
        
        if (windows.size() == 1) {
            return windows.at(0);
        }

        return nullptr;
    }

    void window_manager::process_mouse() {
        const auto win = get_window_under_cursor();

        static bool was_left_clicked = false;
        static bool is_dragging = false, is_resizing = false;
        static bool titlebar_hovered = false, resize_hovered = false;

        static window_ptr target_window = nullptr; // NOLINT(clang-diagnostic-exit-time-destructors)

        if (win) {
            titlebar_hovered = input::mouse_in_bounds(win->get_min(), { win->get_size().x, win->get_min().y + win->get_titlebar_height() });
            resize_hovered = input::mouse_in_bounds(win->get_size() - ImVec2(10, 10), win->get_size());
        }

        if (resize_hovered && win || is_resizing) {
            drawing::set_cursor(ImGuiMouseCursor_ResizeNWSE);
        }

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            if (!was_left_clicked && win) {
                was_left_clicked = true;
                move_to_front(win, true);         

                if (titlebar_hovered) {
                    is_dragging = true;
                    target_window = win;
                }
                else if (resize_hovered) {
                    is_resizing = true;
                    target_window = win;
                }
            }
        }

        if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
            if (target_window) {
                if (is_dragging) {
                    target_window->event(window_event::drag_start);
                }
                else if (is_resizing) {
                    target_window->event(window_event::resize_start);
                }
            }
        }

        if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            if (target_window) {
                if (is_dragging) {
                    target_window->event(window_event::drag_end);
                    is_dragging = false;
                }
                else if (is_resizing) {
                    drawing::set_cursor(ImGuiMouseCursor_Arrow);
                    target_window->event(window_event::resize_end);
                    is_resizing = false;
                }
            }

            was_left_clicked = false;
        }
    }

    void window_manager::render() {
        for (auto &win : windows_) {
            const auto pos = win->get_min();
            const auto size = win->get_max();

            if (win == active_window_) {
                //drawing::rect_shadow({ pos.x - 1, pos.y - 1 }, { size.x + 1, size.y + 1 }, color::active_window_glow, 15.0f, {});
            }

            win->render();

            for (auto &child : win->get_children()) {
                child->render();
            }
        }
    }

    void window_manager::new_frame() {
        process_mouse();
        render();
    }

    void window_manager::end_frame() {

    }
}
