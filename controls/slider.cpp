/*
 * Copyright (c) 2021, EternityX <eternity@enevade.org>
 *
 * SPDX License Identifier: BSD-3-Clause
 */

#include "slider.h"

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"
#include "../wrapped/platform.h"

namespace deadcell::gui {
    template <typename T>
    slider<T>::slider(const std::string_view text, const std::string_view unique_id, T *var, T value_min, T value_max, const std::string_view format)
        : text_(text), var_(var), value_min_(value_min), value_max_(value_max), format_(format) {
        assert(!unique_id.empty());
        assert(var);

        unique_ids_.insert(std::pair(unique_id, this));
    }

    template <typename T>
    slider<T>::slider(const std::string_view text, const std::string_view unique_id, T *var, T value_min, T value_max, std::function<std::string(T)> format)
        : text_(text), var_(var), value_min_(value_min), value_max_(value_max), format_func_(format) {
        assert(!unique_id.empty());
        assert(var);

        unique_ids_.insert(std::pair(unique_id, this));
    }

    template <typename T>
    void slider<T>::event(base_event &e) {
        object::event(e);
    }

    template <typename T >
    void slider<T>::layout(layout_item &overlay, layout_item &parent) {

    }

    template <typename T >
    void slider<T>::render() {

    }

    template class slider<int>;
    template class slider<float>;
    template class slider<double>;
}