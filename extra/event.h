#pragma once

namespace deadcell::gui {
    class base_event {
    private:
        int type_ = invalid;
        bool accepted_ = true;

    public:
        enum type_e {
            invalid = 0,
            mouse_click,
            mouse_down,
            mouse_up,
            mouse_move,
            mouse_hover,
        };

        base_event() { }

        base_event(const int type)
            : type_(type) { }

        int type() const {
            return type_;
        }

        bool is_accepted() const {
            return accepted_;
        }

        // Prevent events from being passed down to any children.
        void accept() {
            accepted_ = true;
        }

        // Allow events to be passed down to any children.
        void ignore() {
            accepted_ = false;
        }
    };

    class window_event : public base_event {
    private:
    public:
        enum type_e {
            drag_start,
            drag_end,
            resize_start,
            resize_end,
        };

        window_event()
            : base_event() {
            
        }

#pragma warning(suppress: 26812)
        explicit window_event(const type_e type)
            : base_event(type) {
        }
    };
}