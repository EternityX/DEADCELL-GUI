#include "../instance.h"
#include "window_manager.h"

namespace deadcell::gui {
    void window_manager::add_window(const window_ptr &win) {
        const bool is_first_window = windows_.empty();

        windows_.push_back(win);

        if (is_first_window) {
            set_active_window(win);
        }
    }

    void window_manager::remove_window(const window_ptr& win) {
        const auto it = std::ranges::find_if(windows_, [&win](const window_ptr &ptr) {
            return ptr.get() == win.get();
        });

        if (it != windows_.end()) {
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

    void window_manager::handle_drag() {
        
    }

    void window_manager::process_mouse() {

    }

    void window_manager::render() {
        for (auto &win : windows_) {
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
