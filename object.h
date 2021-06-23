#pragma once

#include "gui.h"

#include <memory>
#include <string>
#include <vector>

namespace deadcell::gui {
    class object : public std::enable_shared_from_this<object> {
    private:
        std::shared_ptr<object> parent_ = nullptr;
        std::vector<std::shared_ptr<object>> children_;

    protected:
        object(std::shared_ptr<object> parent = nullptr);

    public:
        virtual ~object();

        void add_child(const std::shared_ptr<object> &object);
        void remove_child(const std::shared_ptr<object> &object);
    };
}