#pragma once

namespace Component
{
	class component_base
	{
	public:
		component_base() = default;
		component_base(component_base const&)				= delete;
		component_base(component_base&&)					= delete;
		component_base& operator= (component_base const&)	= delete;
		component_base& operator= (component_base&&)		= delete;

		virtual ~component_base() {}
	};
}