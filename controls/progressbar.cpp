#include "progressbar.h"

#include "../wrapped/drawing.h"
#include "../wrapped/input.h"
#include "../wrapped/platform.h"

namespace deadcell::gui {
    progressbar::progressbar(const std::string_view text, std::string_view unique_id,
        std::function<void()> completed_callback, std::function<void()> tick_callback)
        : text_(text), completed_func_(std::move(completed_callback)), tick_func_(std::move(tick_callback)) {

        assert(!unique_id.empty());
        unique_ids_.insert(std::pair(unique_id, this));
    }

    progressbar::progressbar(const std::string_view text, std::string_view unique_id, const float width,
        std::function<void()> completed_callback, std::function<void()> tick_callback)
        : text_(text), completed_func_(std::move(completed_callback)), tick_func_(std::move(tick_callback)) {

        assert(!unique_id.empty());
        unique_ids_.insert(std::pair(unique_id, this));
        size_ = { width, 6.0f };
    }

    void progressbar::event(base_event &e) {
        object::event(e);
    }

    void progressbar::layout(layout_item &overlay, layout_item &parent) {

    }

    void progressbar::render() {
        if (!visible_) {
            return;
        }
    }
}