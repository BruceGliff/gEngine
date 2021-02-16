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
		component_base(component_base const&)				= delete;
		component_base(component_base&&)					= delete;
		component_base& operator= (component_base const&)	= delete;
		component_base& operator= (component_base&&)		= delete;

		Property::ICompound * GetParent() const noexcept
		{
			return parent_;
		}
		void * SetParent(Property::ICompound * parent) noexcept
		{
			parent_ = parent;
		}

		virtual ~component_base() {}
	};
}