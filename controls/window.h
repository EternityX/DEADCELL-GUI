#pragma once

#include "../controls/object.h"

namespace deadcell::gui {
    class window : public object {
    private:
        bool visible_ = true;

        ImVec2 min_;
        ImVec2 max_;
    public:
        window();
        void event();

        void set_min_max(ImVec2 min, ImVec2 max);

        bool is_visible() const;

        void render() override;
    };
}