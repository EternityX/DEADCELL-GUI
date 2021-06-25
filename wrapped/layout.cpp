#define LAY_IMPLEMENTATION

#include "layout.h"

layout_item::layout_item(lay_context* ctx, lay_id item) {
    ctx_ = ctx;
    item_ = item;
}

layout_item::layout_item() {
    ctx_ = nullptr;
    item_ = LAY_INVALID_ID;
}

layout_item::layout_item(lay_context* ctx) {
    ctx_ = ctx;
    item_ = lay_item(ctx);
}

lay_vec2 layout_item::get_size() const {
    return lay_get_size(ctx_, item_);
}

lay_vec4 layout_item::get_margins() const {
    return lay_get_margins(ctx_, item_);
}

lay_vec4 layout_item::get_rect() const {
    return lay_get_rect(ctx_, item_);
}

void layout_item::set_size(const lay_vec2 &size) {
    lay_set_size(ctx_, item_, size);
}

void layout_item::set_margins(const lay_vec4 &margins) {
    lay_set_margins(ctx_, item_, margins);
}

void layout_item::set_size(lay_scalar x, lay_scalar y) {
    lay_set_size_xy(ctx_, item_, x, y);
}

void layout_item::set_margins(lay_scalar left, lay_scalar top, lay_scalar right, lay_scalar bottom) {
    lay_set_margins_ltrb(ctx_, item_, left, top, right, bottom);
}

void layout_item::run() {
    lay_run_item(ctx_, item_);
}

void layout_item::clear_item_break() {
    lay_clear_item_break(ctx_, item_);
}

void layout_item::push(const layout_item &child) {
    lay_push(ctx_, item_, child.item_);
}

void layout_item::insert(const layout_item &child) {
    lay_insert(ctx_, item_, child.item_);
}

void layout_item::set_contain(int flags) {
    lay_set_contain(ctx_, item_, flags);
}

void layout_item::set_behave(int flags) {
    lay_set_behave(ctx_, item_, flags);
}

bool layout_item::is_valid() const {
    return item_ != LAY_INVALID_ID;
}

layout_item& layout_item::size(const lay_vec2 &size) {
    set_size(size);

    return *this;
}

layout_item& layout_item::size(float x, float y) {
    set_size(x, y);

    return *this;
}

layout_item& layout_item::margins(const lay_vec4 &margins) {
    set_margins(margins);

    return *this;
}

layout_item& layout_item::margins(lay_scalar left, lay_scalar top, lay_scalar right, lay_scalar bottom) {
    set_margins(left, top, right, bottom);

    return *this;
}

layout_item& layout_item::contain(int flags) {
    set_contain(flags);

    return *this;
}

layout_item& layout_item::behave(int flags) {
    set_behave(flags);

    return *this;
}

layout_item layout_item::new_item(int behave, int contain) {
    auto new_item = layout_item(ctx_, lay_item(ctx_));

    new_item.set_behave(behave);
    new_item.set_contain(contain);

    insert(new_item);

    return new_item;
}

layout_item layout_item::begin() const {
    return layout_item(ctx_, lay_first_child(ctx_, item_));
}

layout_item layout_item::end() const {
    return layout_item(ctx_, lay_last_child(ctx_, item_));
}

layout_item layout_item::next() const {
    return layout_item(ctx_, lay_next_sibling(ctx_, item_));
}

bool layout_item::operator==(const layout_item &rhs) const {
    return item_ == rhs.item_;
}

bool layout_item::operator!=(const layout_item &rhs) const {
    return item_ != rhs.item_;
}

layout::layout() {
    lay_init_context(&ctx);
}

layout::~layout() {
    lay_destroy_context(&ctx);
}

layout_item layout::item(int behave, int contain) {
    auto item = layout_item(&ctx);

    item.set_behave(behave);
    item.set_contain(contain);

    return item;
}

void layout::run() {
    lay_run_context(&ctx);
}

void layout::reset() {
    lay_reset_context(&ctx);
}

void layout::reserve(lay_id capacity) {
    lay_reserve_items_capacity(&ctx, capacity);
}
