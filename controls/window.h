#pragma once

#include "../controls/object.h"

namespace deadcell::gui {
    class window : public object {
    private:
        bool visible_ = true;
    
    public:
        window();

        bool is_visible() const;

        void draw() override;
    };
}