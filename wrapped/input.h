/*
 * Copyright (c) 2021, EternityX <eternity@enevade.org>
 *
 * SPDX License Identifier: BSD-3-Clause
 */

#pragma once

#include "../config.h"
#include "types.h"

namespace deadcell::gui::input {
	enum mouse_button_e {
		mouse_left,
		mouse_middle,
		mouse_right,
		mouse_x1,
		mouse_x2
	};

	point get_mouse_pos();
	point get_mouse_delta();

	float get_wheel_delta();

	bool is_mouse_clicked(int mouse_button, bool repeat = false);
	bool is_mouse_down(int mouse_button);
	bool is_mouse_released(int mouse_button);
	bool is_mouse_in_bounds(const point& position, const point& size);
}