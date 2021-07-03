#include "textbox.h"

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"
#include "../wrapped/platform.h"

deadcell::gui::textbox::textbox(std::string_view unique_id) {
	unique_ids_.insert(std::pair(unique_id, this));
}

void deadcell::gui::textbox::event(base_event &e) {

}

void deadcell::gui::textbox::layout(layout_item &overlay, layout_item &parent) {

}

void deadcell::gui::textbox::render() {

}

