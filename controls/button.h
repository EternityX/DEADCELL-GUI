#pragma once

#include "../object.h"

namespace deadcell::gui {
    class button : public object {
    private:
        bool visible_ = true;

    public:
        button();

        bool is_visible() const;
    };
}