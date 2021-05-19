#pragma once

namespace Property
{
    class ICompound;
}


namespace Component
{
    class component_base
    {
        Property::ICompound * parent_ = nullptr;
    public:
        component_base() = default;
        component_base(component_base const&)                = delete;
        component_base(component_base&& other) noexcept;
        component_base& operator= (component_base const&)    = delete;
        component_base& operator= (component_base&&)        = delete;

        Property::ICompound * GetParent() const noexcept;
        void SetParent(Property::ICompound * parent) noexcept;

        virtual ~component_base() {}
    };
}