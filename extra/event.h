#pragma once

namespace deadcell::gui {
    class base_event {
    private:
        int type_ = invalid;
        bool accepted_ = true;

    public:
        enum type_e {
            invalid = 0,
            key_pressed,
            key_down,
            key_up,
            mouse_click,
            mouse_down,
            mouse_up,
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

        // Prevents events from being passed down to any children.
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
            mouse_move,
            left_mouse_down,
            left_mouse_up,
            right_mouse_down,
            right_mouse_up,
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