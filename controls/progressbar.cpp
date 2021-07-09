#include "progressbar.h"

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"
#include "../wrapped/platform.h"

namespace deadcell::gui {
    template <typename T>
    static T scale(T value, T in_min, T in_max, T out_min, T out_max) {
        return static_cast<T>((value - in_min) * (out_max - out_min) / static_cast<T>(in_max - in_min) + out_min);
    }

    template <typename T>
    void progressbar<T>::event(base_event &e) {
        object::event(e);
    }

    template <typename T >
    void progressbar<T>::layout(layout_item &overlay, layout_item &parent) {

    }

    template <typename T>
    void progressbar<T>::render() {
        if (size_.is_empty() || !visible_) {
            return;
        }

        auto progress_width = scale<T>(progress_, progress_min_, progress_max_, 0, static_cast<T>(size_.x));

        drawing::push_clip_rect(pos_, size_);
        {
            drawing::rect_filled(pos_, size_, colors::progress_background, 3.0f);

            if (static_cast<float>(progress_width) >= 3.0f) {
                drawing::rect_filled(pos_, { static_cast<float>(progress_width), size_.y }, colors::progress_filled, 3.0f);
            }
        }
        drawing::pop_clip_rect();
    }

    template class progressbar<int>;
    template class progressbar<float>;
    template class progressbar<double>;
}