#pragma once

#include "../extra/event.h"

#include <memory>
#include <vector>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

namespace deadcell::gui {
    class object : public std::enable_shared_from_this<object> {
    private:
        std::shared_ptr<object> parent_ = nullptr;
        std::vector<std::shared_ptr<object>> children_;

        using object_ptr = std::shared_ptr<object>;

    protected:
        explicit object(object_ptr parent = nullptr);

    public:
        virtual ~object();

        virtual void event(const base_event &e) { }
        virtual void render() { }

        void dispatch_event(const base_event &e, const object_ptr &stay_within);

        void add_child(const object_ptr &object);
        void remove_child(const object_ptr &object);
        std::shared_ptr<object> get_child(const object_ptr &object);
        std::vector<std::shared_ptr<object>> get_children() const;
    };
}