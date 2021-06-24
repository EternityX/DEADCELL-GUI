#pragma once

#include "../controls/object.h"

namespace deadcell::gui {
    class button : public object {
    private:
        bool visible_ = true;

    protected:
        std::string unique_id_;

    public:
        button(std::string_view unique_id);

        bool is_visible() const;

        std::string get_class_name() override { return "button()"; }
    };
}