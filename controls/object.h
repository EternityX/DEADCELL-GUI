#pragma once

#include "../extra/event.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

#include <map>
#include <memory>
#include <vector>
#include <sstream>
#include <utility>
#include <string>
#include <xstring>

namespace deadcell::gui {
    class object : public std::enable_shared_from_this<object> {
    private:
        using object_ptr = std::shared_ptr<object>;

        std::shared_ptr<object> parent_ = nullptr;
        std::vector<object_ptr> children_;

    protected:
        std::map<std::string, object_ptr> unique_ids_;

    public:
        object();
        virtual ~object();

        virtual void event(const base_event &e) { }
        virtual void render() { }
        virtual std::string get_class_name() { return "object()"; }

        void dispatch_event(const base_event &e, const object_ptr &stay_within);

        void add_child(const object_ptr &object);
        void remove_child(const object_ptr &object);
        void remove_all_children();
        std::shared_ptr<object> get_parent() const;
        void remove_from_parent();
        std::shared_ptr<object> get_child(const object_ptr &object);
        std::vector<object_ptr> get_children() const;
        bool is_ancestor(const object_ptr &object);

        std::string build_class_tree();
    };
}
