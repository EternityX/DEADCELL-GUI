#include "control.h"
#include "object.h"


#include <utility>

namespace deadcell::gui {
    object::object(object_ptr parent)
        : parent_(std::move(parent)) {
        if (parent_) {
            parent_->add_child(shared_from_this());
        }
    }

    object::~object() {
        auto children = std::move(children_);

        for (auto &child : children) {
            child->parent_ = nullptr;
        }

        if (parent_) {
            parent_->remove_child(shared_from_this());
        }
    }

    void object::dispatch_event(const base_event &e, const object_ptr &stay_within) {
        auto target = shared_from_this();
        do {
            target->event(e);
            target = target->parent_;

            if (target == stay_within) {
                return;
            }
        } while (target && !e.is_accepted());
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
}
