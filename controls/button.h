#pragma once

#include <functional>

#include "../controls/object.h"

namespace deadcell::gui {
    class button : public object {
    private:
        std::string text_;

        bool visible_ = true;
        bool hovered_ = false;
        bool mouse_clicked_ = false;

        point pos_ = {25, 55};
        point size_;

        std::function<void()> func_;
    protected:
        std::string unique_id_;

    public:
        button(std::string_view text, std::string_view unique_id, std::function<void()> callback);
        button(std::string_view text, std::string_view unique_id, point size, std::function<void()> callback);

        void set_position_size(const point &pos, const point &size) {
            pos_ = pos;
            size_ = size;
        }

        void set_position(const point &pos) {
            pos_ = pos;
        }

        void set_size(const point &size) {
            size_ = size;
        }

        void set_visible(const bool visible) {
            visible_ = visible;
        }

        bool is_visible() const;

        void event(base_event &e) override;
        void layout(layout_item &overlay, layout_item &parent) override;
        void render() override;

        std::string get_class_name() override { return "button()"; }
    };
}