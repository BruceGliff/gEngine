#include "actor.h"
#include <iostream>
#include <string>

#include "../debug/debug.h"

Actor::placeable_obj::placeable_obj() : actor_base{}, anchor{ 0.f, 0.f, 3.f }
{}

Actor::placeable_obj::placeable_obj(glm::vec3 const& pos) : actor_base{}, anchor{pos}
{}

glm::vec3& Actor::placeable_obj::GetPosition() noexcept
{
	return anchor;
}

glm::vec3 const& Actor::placeable_obj::GetPosition() const noexcept
{
	return anchor;
}

void Actor::component_attachable::attach_component(std::string const& comp_name, Component::component_base * component)
{
	auto&& it = components_map.find(comp_name);
	if (it != components_map.end())
	{
		delete it->second;
		it->second = component;
		return;
	}

	components_map[comp_name] = component;
}

Component::component_base * Actor::component_attachable::GetComponent(std::string const& comp_name) const
{
	auto&& it = components_map.find(comp_name);
	if (it != components_map.end())
	{
		return it->second;
	}

	gERROR(std::string{ "cannot find component with name: " + comp_name });
}

void Actor::moveable_obj::SetPosition(glm::vec3 const& pos)
{
	anchor = pos;
}

Actor::moveable_obj::moveable_obj()
{}
