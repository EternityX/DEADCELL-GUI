/*
 * Copyright (c) 2021, EternityX <eternity@enevade.org>
 *
 * SPDX License Identifier: BSD-3-Clause
 */

#pragma once

#include "../extra/event.h"
#include "../config.h"

//#define IMGUI_DEFINE_MATH_OPERATORS
//#include <imgui.h>
//#include <imgui_internal.h>

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <xstring>

#include "../wrapped/layout.h"

namespace deadcell::gui {
    class object : public std::enable_shared_from_this<object> {
    private:
        using object_ptr = std::shared_ptr<object>;

        std::shared_ptr<object> parent_ = nullptr;
        std::vector<object_ptr> children_;

        layout_item root_row_;

    protected:
        std::map<std::string, object_ptr> unique_ids_;

    public:
        object();
        virtual ~object();

        virtual void event(base_event &e) { if (get_children().empty()) { e.accept(); } }
        virtual void layout(layout_item &overlay, layout_item &parent);
        virtual void render() { }
        virtual std::string get_class_name() { return "object"; }

        void dispatch_event(base_event e, const object_ptr &stay_within = nullptr);

        void add_child(const object_ptr &object);
        void remove_child(const object_ptr &object);
        void remove_all_children();
        std::shared_ptr<object> get_parent() const;
        void remove_from_parent();
        std::shared_ptr<object> get_child(const object_ptr &object);
        std::vector<object_ptr> get_children() const;
        bool is_ancestor(const object_ptr &object);

        std::string build_class_tree();
        std::string get_unique_id();
    };
}
