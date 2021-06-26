#include "button.h"

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"

namespace deadcell::gui {
    button::button(const std::string_view unique_id) {
        unique_ids_.insert(std::pair(unique_id, this));
    }

    bool button::is_visible() const {
		return visible_;
    }

    void button::event(base_event &e) {
        if (e.type() == base_event::mouse_down) {

        }

        object::event(e);
    }

    void button::render() {
        drawing::rect_filled(min_, max_, color::body_darker, 4.0f);
    }
}
