#pragma once

#include "../gui.h"

namespace deadcell::gui::input {
	bool mouse_in_bounds(ImVec2 position, ImVec2 size);
}