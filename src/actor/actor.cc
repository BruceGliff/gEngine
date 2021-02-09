#include "actor.h"
#include <iostream>
#include <string>

#include "actorDEF.h"

#include "../debug/debug.h"

Actor::actor & Actor::actor::AttachComponent(std::string const& comp_name, Component::component_base * component)
{	
	// to get hints when insert propertied into define;
	using namespace Property;
	// firstly make pair
	// secondly replace it


	ComponentAggregation aggregation;
	aggregation.first = component;

	INSERT_PROPERTY(IDrawable);
	INSERT_PROPERTY(IPhysicaly);


	auto&& it = components.find(comp_name);
	if (it != components.end())
	{
		// delete old components
		ComponentAggregation oldAggr = std::move(it->second);
		Component::component_base * oldComp = it->second.first;
		it->second = std::move(aggregation);
		remove_properties_from(oldAggr.second);

		delete oldComp;

		return *this;
	}

	components[comp_name] = std::move(aggregation);

	return *this;
}

Component::component_base * Actor::actor::GetComponent(std::string const& comp_name) const noexcept
{
	auto&& it = components.find(comp_name);
	if (it != components.end())
	{
		return it->second.first;
	}

	return nullptr;
}

Component::component_base * Actor::actor::DetachComponent(std::string const& comp_name) noexcept
{
	auto && it = components.find(comp_name);
	if (it != components.end())
	{
		Component::component_base * oldComp = it->second.first;
		remove_properties_from(it->second.second);
		components.erase(it);

		return oldComp;
	}

	return nullptr;
}

Actor::actor & Actor::actor::DeleteComponent(std::string const& comp_name) noexcept
{
	auto && it = components.find(comp_name);
	if (it != components.end())
	{
		Component::component_base * oldComp = it->second.first;
		remove_properties_from(it->second.second);
		components.erase(it);

		delete oldComp;
	}
}

void Actor::actor::remove_properties_from(std::vector<std::list<void *>::iterator> const & prop_array) noexcept
{
	for (auto && property : prop_array)
	{
		REMOVE_PROPERTY(IDrawable);
		REMOVE_PROPERTY(IPhysicaly);
	}
}

Actor::actor::~actor()
{
	for (auto && x : components)
		delete x.second.first;
}

Actor::actor & Actor::actor::Process(Renderer::ShaderProgram const & sp, Geometry::Transformation const & tr) const
{
	for (auto && x : Array_IDrawable)
	{
		Property::IDrawable * ptr = reinterpret_cast<Property::IDrawable *>(x);
		ptr->Draw(sp);
	}
}