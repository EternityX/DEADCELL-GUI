
#include "object.h"

#include <iostream>

namespace deadcell::gui {
    object::object() = default;

    object::~object() {
        for (auto children = std::move(children_); auto &child : children) {
            child->parent_ = nullptr;
        }

        if (parent_) {
            parent_->remove_child(shared_from_this());
        }
    }

    void object::layout(layout_item &overlay, layout_item &parent) {
        root_row_ = parent
            .new_item(LAY_HFILL, LAY_ROW)
            .margins(0.0f, 0.0f, 0.0f, 8.0f);
    }

    void object::dispatch_event(base_event e, const object_ptr &stay_within) {
        auto target = shared_from_this();

        target->event(e);

        if (target == stay_within) {
            return;
        }

        for (auto &child : children_) {
            child->dispatch_event(e, stay_within);
        }
    }

    void object::add_child(const object_ptr &object) {
        object->parent_ = shared_from_this();
        children_.emplace(children_.begin(), object);
    }

    void object::remove_child(const object_ptr &object) {
        for (size_t i = 0; i < children_.size(); ++i) {
            auto &child = children_.at(i);
            if (child != object) {
                continue;
            }

            child->parent_ = nullptr;
            children_.erase(children_.begin() + i);
        }
    }

    void object::remove_all_children() {
        while (!children_.empty()) {
            children_.front()->remove_from_parent();
        }
    }

    std::shared_ptr<object> object::get_parent() const {
        return parent_;
    }

    void object::remove_from_parent() {
        if (parent_) {
            parent_->remove_child(shared_from_this());
        }
    }

    std::shared_ptr<object> object::get_child(const object_ptr &object) {
        for (auto &child : children_) {
            if (child == object) {
                return child;
            }
        }

        return nullptr;
    }

    std::vector<std::shared_ptr<object>> object::get_children() const {
        return children_;
    }

    bool object::is_ancestor(const object_ptr &object) {
        if (object == shared_from_this()) {
            return false;
        }

        for (auto ancestor = object->parent_; ancestor; ancestor = ancestor->parent_) {
            if (ancestor == shared_from_this()) {
                return true;
            }
        }

        return false;
    }

    std::string object::build_class_tree() {
        auto reverse_map = [&](const std::map<std::string, object_ptr> &map, const object_ptr &object) -> std::string {
            for (const auto &[key, value] : map) {
                if (value == object) {
                    return key;
                }
            }

            return {};
        };

        std::stringstream ss;
        ss << "0x" << std::hex << shared_from_this().get() << std::dec
            << " [" << get_class_name() << ":" << reverse_map(unique_ids_, shared_from_this()) << "]\n";

        for (auto &child : children_) {
            ss << "  - " << "0x" << std::hex << child.get() << std::dec
                << " [" << child->get_class_name() << ":" << reverse_map(child->unique_ids_, child) << "]\n";
        }

        return ss.str();
    }

    std::string object::get_unique_id() {
        for (const auto &[key, value] : unique_ids_) {
            if (value == shared_from_this()) {
                return key;
            }
        }

        return {};
    }
}
