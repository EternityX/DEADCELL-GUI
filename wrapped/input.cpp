#include "input.h"

#include <cmath>

namespace deadcell::gui::input {
	point get_mouse_pos() {
		const auto& io = ImGui::GetIO();

		return { io.MousePos.x, io.MousePos.y };
	}

	point get_mouse_delta() {
		const auto& io = ImGui::GetIO();

		return { io.MouseDelta.x, io.MouseDelta.y };
	}

	float get_wheel_delta() {
		return ImGui::GetIO().MouseWheel;
	}

	bool is_mouse_clicked(int mouse_button, bool repeat) {
		return ImGui::IsMouseClicked(mouse_button, repeat);
	}

	bool is_mouse_down(int mouse_button) {
		return ImGui::IsMouseDown(mouse_button);
	}

	bool is_mouse_released(int mouse_button) {
		return ImGui::IsMouseReleased(mouse_button);
	}

	bool is_in_bounds(const point& position, const point& size) {
		const auto mouse_pos = get_mouse_pos();

		return mouse_pos.x >= position.x && mouse_pos.y >= position.y
			&& mouse_pos.x <= position.x + size.x && mouse_pos.y <= position.y + size.y;
	}
}
