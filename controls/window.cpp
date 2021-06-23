#include "window.h"

#include "../wrapped/drawing.h"

namespace deadcell::gui {
	window::window() {

	}

    bool window::is_visible() const {
		return visible_;
    }

    void window::draw() {
        drawing::rect_filled({ 25, 25 }, { 250, 250 }, IM_COL32(255, 255, 255, 255), 0.0f, 0);
    }
}
