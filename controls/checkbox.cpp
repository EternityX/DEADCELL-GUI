#include "checkbox.h"

deadcell::gui::checkbox::checkbox(const std::string_view text, std::string_view unique_id, bool *var, std::function<void()> callback)
    : text_(text), var_(var), func_(std::move(callback)) {
    assert(!unique_id.empty());
    assert(callback);

    unique_ids_.insert(std::pair(unique_id, this));
}

void deadcell::gui::checkbox::event(base_event &e) {
}

void deadcell::gui::checkbox::layout(layout_item &overlay, layout_item &parent) {
}

void deadcell::gui::checkbox::render() {
}
