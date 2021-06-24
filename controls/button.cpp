#include "button.h"

namespace deadcell::gui {
    button::button(const std::string_view unique_id) {
        unique_ids_.insert(std::pair(unique_id, this));
    }

    bool button::is_visible() const {
		return visible_;
    }
}
