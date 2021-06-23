#include "control.h"
#include "object.h"

#include <utility>

namespace deadcell::gui {
    object::object(std::shared_ptr<object> parent)
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

    void object::draw() {

    }

    void object::add_child(const std::shared_ptr<object> &object) {
        object->parent_ = shared_from_this();
        children_.emplace(children_.begin(), object);
    }

    void object::remove_child(const std::shared_ptr<object> &object) {
        for (size_t i = 0; i < children_.size(); ++i) {
            auto &child = children_.at(i);
            if (child != object) {
                continue;
            }

            child->parent_ = nullptr;
            children_.erase(children_.begin() + i);
        }
    }

    std::shared_ptr<object> object::get_child(const std::shared_ptr<object> &object) {
        for (auto &child : children_) {
            if (child == object) {
                return child;
            }
        }

        return nullptr;
    }
}
