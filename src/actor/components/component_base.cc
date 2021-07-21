#include "component_base.h"

#include <algorithm>

using namespace NSComponent;

NSProperty::ICompound * component_base::GetParent() const noexcept {
    return parent_;
}
void component_base::SetParent(NSProperty::ICompound * parent) noexcept {
    parent_ = parent;
}

component_base::component_base(component_base&& other) noexcept {
    std::swap(parent_, other.parent_);
}