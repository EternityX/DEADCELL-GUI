#include "input.h"

namespace deadcell::gui::input {
	bool mouse_in_bounds(const ImVec2 position, const ImVec2 size) {
		const auto &io = ImGui::GetIO();

		if (io.MousePos.x >= position.x && io.MousePos.y >= position.y
			&& io.MousePos.x <= size.x && io.MousePos.y <= size.y) {
			return true;
		}

		return false;
	}
}