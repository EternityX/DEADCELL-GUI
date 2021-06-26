#pragma once

#include "../controls/object.h"

namespace deadcell::gui {
    class button : public object {
    private:
        bool visible_ = true;

        point min_ = { 10, 10 };
        point size_ = { 120, 45 };

    protected:
        std::string unique_id_;

    public:
        button(std::string_view unique_id);

        bool is_visible() const;

        void event(base_event &e) override;
        void render() override;

        std::string get_class_name() override { return "button()"; }
    };
}