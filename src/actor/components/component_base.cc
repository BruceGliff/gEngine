#include "component_base.h"


Property::ICompound * Component::component_base::GetParent() const noexcept
{
    return parent_;
}
void Component::component_base::SetParent(Property::ICompound * parent) noexcept
{
    parent_ = parent;
}

Component::component_base::component_base(component_base&& other) noexcept
{
    parent_ = other.parent_;
    other.parent_ = nullptr;
}