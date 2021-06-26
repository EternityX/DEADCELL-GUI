#include "input.h"

#include <cmath>

namespace deadcell::gui::input {
	bool mouse_in_bounds(const ImVec2 position, const ImVec2 size) {
		const auto &io = ImGui::GetIO();

		return io.MousePos.x >= std::floor(position.x)
			&& io.MousePos.y >= std::floor(position.y)
			&& io.MousePos.x <= std::floor(position.x + size.x)
			&& io.MousePos.y <= std::floor(position.y + size.y);
	}
}