#include "actor.h"
#include <iostream>
#include <string>

#include "actorDEF.h"

#include "../debug/debug.h"
#include "../geometry/geometry_base.h"

Actor::actor::actor(actor&& otherActor) noexcept :
	Resources::Entity{std::move(otherActor)},
	Component::component_base{std::move(otherActor)},
	Property::IMoveable{std::move(otherActor)}
{
	components = std::move(otherActor.components);
	
	// set new parent to components
	for (auto&& x : components)
	{
		x.second.first->SetParent(this);
	}

	MOVE_PROPERTY(IDrawable);
	MOVE_PROPERTY(ICompound);
}


Actor::actor & Actor::actor::AttachComponent(std::string const& comp_name, Component::component_base * component)
{	
	// to get hints when insert propertied into define;
	using namespace Property;
	// firstly make pair
	// secondly replace it

	// set this class as parent for component
	component->SetParent(this);

	// Aggregation is a pair of component and array of properties of the component
	ComponentAggregation aggregation;
	aggregation.first = component;

	INSERT_PROPERTY(IDrawable);
	INSERT_PROPERTY(ICompound);
	//INSERT_PROPERTY(IPhysicaly);


	auto&& it = components.find(comp_name);
	if (it != components.end())
	{
		// delete old components
		// TODO this is work part(maybe)
		// ComponentAggregation oldAggr = std::move(it->second);
		// Component::component_base * oldComp = it->second.first;
		// it->second = std::move(aggregation);
		// remove_properties_from_generated_arrays(oldAggr.second);

		std::swap(aggregation, it->second);
		delete aggregation.first;

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
		remove_properties_from_generated_arrays(it->second.second);
		components.erase(it);

		oldComp->SetParent(nullptr);
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
		remove_properties_from_generated_arrays(it->second.second);
		components.erase(it);

		delete oldComp;
	}

	return *this;
}

void Actor::actor::remove_properties_from_generated_arrays(std::vector<std::list<void *>::iterator> const & prop_array) noexcept
{
	for (auto && property : prop_array)
	{
		REMOVE_PROPERTY(IDrawable);
		REMOVE_PROPERTY(ICompound);
		//REMOVE_PROPERTY(IPhysicaly);
	}
}

Actor::actor::~actor()
{
	for (auto && x : components)
		delete x.second.first;
}

#include <iostream>
void Actor::actor::Process(Geometry::Transformation const & tr)
{
	// TODO check is it is possible to do with define
	//PROCESS_PROPERTY(IPhysicaly, DoPhysic, sp, tr);

	Geometry::Transformation const newTr{ tr + Geometry::Transformation{GetPosition(), GetRotation(), GetScale()} };

	for (auto && x : Array_IDrawable)
	{
		reinterpret_cast<Property::IDrawable *>(x)->Draw(newTr);
	}
	for (auto&& x : Array_ICompound)
	{
		reinterpret_cast<Property::ICompound*>(x)->Process(newTr);
	}

}