#include "window.h"

#include "../wrapped/drawing.h"

namespace deadcell::gui {
	window::window() {

	}

    void window::set_min_max(const ImVec2 min, const ImVec2 max) {
        min_ = min;
        max_ = max;
    }

    bool window::is_visible() const {
		return visible_;
    }

    void window::handle_drag_event() {
	    
	}

    void window::event(const base_event &e) {
        if (e.type() == window_event::drag_start) {
            handle_drag_event();
        }
    }

    void window::render() {
        drawing::rect_filled(min_, max_, IM_COL32(255, 255, 255, 255), 0.0f, 0);
        drawing::rect_filled(min_, max_, IM_COL32(0, 255, 255, 255), 23.0f, 0);
    }
}
