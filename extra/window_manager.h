#pragma once

#include "../controls/window.h"

namespace deadcell::gui {
    using window_ptr = std::shared_ptr<window>;

    class window_manager {
    private:
        std::shared_ptr<window> active_window_;
        std::vector<std::shared_ptr<window>> windows_;

        ImVec2 last_mouse_pos_;

        void process_mouse();
        void render();

    public:
        void add_window(const window_ptr &win);
        void remove_window(const window_ptr &win);
        void set_active_window(const window_ptr &win);
        void move_to_front(const window_ptr &win, bool make_active);
        window_ptr get_window_under_cursor();    

        void new_frame();
        void end_frame();
    };
}