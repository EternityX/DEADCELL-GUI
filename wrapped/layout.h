#pragma once

#define LAY_FLOAT 1

#include <imgui.h>
#include <optional>
#include <utility>

#include "../thirdparty/layout.h"

inline std::pair<ImVec2, ImVec2> rect_to_xywh(const lay_vec4 &rect) {
    return std::make_pair(ImVec2(rect[0], rect[1]), ImVec2(rect[2], rect[3]));
}

class layout_item {
    friend class c_element;

    lay_context* ctx_;
    lay_id item_;

public:
    layout_item();
    layout_item(lay_context* ctx, lay_id item);
    layout_item(lay_context* ctx);

    lay_vec2 get_size() const;
    lay_vec4 get_margins() const;
    lay_vec4 get_rect() const;

    void set_size(const lay_vec2 &size);
    void set_margins(const lay_vec4 &margins);

    void set_size(lay_scalar x, lay_scalar y);
    void set_margins(lay_scalar left, lay_scalar top, lay_scalar right, lay_scalar bottom);

    void run();
    void clear_item_break();

    void push(const layout_item &child);
    void insert(const layout_item &child);

    void set_contain(int flags);
    void set_behave(int flags);

    bool is_valid() const;

    layout_item& size(const lay_vec2 &size);
    layout_item& size(float x, float y);
    layout_item& margins(const lay_vec4 &margins);
    layout_item& margins(lay_scalar left, lay_scalar top, lay_scalar right, lay_scalar bottom);
    layout_item& contain(int flags);
    layout_item& behave(int flags);

    layout_item new_item(int behave = 0, int contain = 0);

    layout_item begin() const;
    layout_item end() const;
    layout_item next() const;

    bool operator==(const layout_item &rhs) const;
    bool operator!=(const layout_item &rhs) const;
};

class layout {
    lay_context ctx;

public:
    layout();
    ~layout();

    layout_item item(int behave = 0, int contain = 0);

    void run();
    void reset();
    void reserve(lay_id capacity);
};
