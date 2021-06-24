#pragma once

namespace deadcell::gui {
    class base_event {
    private:
        int type_ = invalid;
        bool accepted_ = true;

    public:
        enum type_e {
            invalid = 0,
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

        void accept() {
            accepted_ = true;
        }

        void ignore() {
            accepted_ = false;
        }
    };

    class window_event : public base_event {
    private:
    public:
        enum type_e {
            drag_start,
            drag_stop,
            drag_move,
        };

        window_event(const type_e type)
            : base_event(type) {
        }
    };
}