#pragma once

namespace NSProperty {
    class ICompound;
} // namespace NSProperty


namespace NSComponent {

class component_base {
    NSProperty::ICompound * parent_ {nullptr};
public:
    component_base() = default;
    component_base(component_base const&)               = delete;
    component_base(component_base&& other) noexcept;
    component_base& operator= (component_base const&)   = delete;
    component_base& operator= (component_base&&)        = delete;

    NSProperty::ICompound * GetParent() const noexcept;
    void SetParent(NSProperty::ICompound * parent) noexcept;

    virtual ~component_base() {}
};

} // namespace Component