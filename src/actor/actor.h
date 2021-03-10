#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <list>
#include <vector>

#include "components/component_base.h"
#include "../properties/properties.h"
#include "../manager/Entity.h"

#include "actorDEF.h"

namespace Renderer
{
	class ShaderProgram;
}
namespace Geometry
{
	class Transformation;
}

namespace Actor
{
	// Class represent main object in scene.
	// It contains components and can be processes to draw or to calculate physics(in future)
	class actor : 	
	// All class must be movable and if it has complex move object, then appears in move constructor as 
	// Resources::Entity{std::move(otherActor)}
					public Resources::Entity,
					public Property::ICompound,
					public Component::component_base,
					public Property::IScalable, 
					public Property::IMoveable, 
					public Property::IRotatable
	{
		// For easy run-time drawing all compomenents separates by their behavior and then running across only one
		// array without casts.
		// Hovewer all pointers in general are the same object, only Component::component_base * represent the
		// physicaly object what can be deleted.
		// We assume that one component may have a lot of properties, that would be represented as void *
		// All operations on component must accompanied with operations on PROPERTIES_ARRAY(INSERT, REMOVE, MOVE, PROCESS)
		// What defined in file actorDEF.h
		typedef std::pair<Component::component_base*, std::vector<std::list<void *>::iterator>> ComponentAggregation;
		typedef std::unordered_map<std::string, ComponentAggregation> ComponentMap;
		ComponentMap components;

		PROPERTIES_ARRAY(IDrawable);
		PROPERTIES_ARRAY(ICompound);
		//PROPERTIES_ARRAY(IPhysicaly);

		// TODO Check if remove throw an exception
		void remove_properties_from_generated_arrays(std::vector<std::list<void *>::iterator> const & prop_array) noexcept;

		

	public:
		actor() = default;
		actor(actor const&)				= delete;
		actor(actor&& otherActor)		noexcept;
		actor& operator= (actor const&) = delete;
		actor& operator= (actor&&)		= delete;

		// Attach component to object by name. Class occupies given resources and releases them by himself
		// Reattaches component if it already exists and deletes old
		actor & AttachComponent(std::string const& comp_name, Component::component_base * );

		// Get component by name. Return nullptr if it was not found. Did not delete from actor
		Component::component_base * GetComponent(std::string const& comp_name) const noexcept;
		// Get component by name with occured cast to necessaty component with type T
        // Return nullptr if cast is failed, or if this component did not found. Did not delete from actor
        template <typename componentType>
        componentType * GetComponentByName(std::string const& comp_name) const noexcept;

		// Get component by name. Return nullptr if it was not found. Removed from actor. Memory did not free
		Component::component_base * DetachComponent(std::string const & comp_name) noexcept;

		// Delete component by name. Do nothing if it is not found
		actor & DeleteComponent(std::string const & comp_name) noexcept;

		// TODO make this via Args...
		// Handle behavior of class. Do drawing or physics or so one
		virtual void Process(Geometry::Transformation const &) override;

		virtual ~actor();
	};



	template <typename componentType>
	componentType * actor::GetComponentByName(std::string const& comp_name) const noexcept
	{
		auto&& it = components.find(comp_name);
		if (it != components.end())
		{
			// TODO may be dynamic_cast<>?
			return static_cast<componentType *>(it->second.first);
		}

		return nullptr;
	}
}

#undef PROPERTIES_ARRAY
#undef INSERT_PROPERTY
#undef REMOVE_PROPERTY
#undef PROCESS_PROPERTY
#undef MOVE_PROPERTY