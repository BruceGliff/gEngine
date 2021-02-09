#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <list>
#include <vector>

#include "components/component_base.h"
#include "../properties/properties.h"

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
	class actor : public Property::IScalable, public Property::IMoveable, public Property::IRotatable
	{
		// For easy run-time drawing all compomenents separates by their behavior and then running across only one
		// array without casts.
		// Hovewer all pointers in general are the same object, only Component::component_base * represent the
		// physicaly object what can be deleted.
		// All operations on component must accompanied with operations on PROPERTIES_ARRAY(INSERT, REMOVE)
		typedef std::pair<Component::component_base*, std::vector<std::list<void *>::iterator>> ComponentAggregation;
		typedef std::unordered_map<std::string, ComponentAggregation> ComponentMap;
		ComponentMap components;

		PROPERTIES_ARRAY(IDrawable);
		PROPERTIES_ARRAY(IPhysicaly);

		// TODO Check if remove throw an exception
		void remove_properties_from(std::vector<std::list<void *>::iterator> const & prop_array) noexcept;

		

	public:
		actor() {};
		actor(actor const&)				= delete;
		actor(actor&&)					= delete;
		actor& operator= (actor const&) = delete;
		actor& operator= (actor&&)		= delete;

		// Attach component to object by name. Class occupies given resources and releases them by himself
		// Reattaches component if it already exists and deletes old
		actor & AttachComponent(std::string const& comp_name, Component::component_base * );

		// Get component by name. Return nullptr if it was not found. Did not delete from actor
		Component::component_base * GetComponent(std::string const& comp_name) const noexcept;

		// Get component by name. Return nullptr if it was not found. Removed from actor  
		Component::component_base * DetachComponent(std::string const & comp_name) noexcept;

		// Delete component by name. Do nothing if it is not found
		actor & DeleteComponent(std::string const & comp_name) noexcept;

		// Handle behavior of class. Do drawing or physics or so one
		actor & Process(Renderer::ShaderProgram const &, Geometry::Transformation const &) const;

		~actor();
	};
}

#undef PROPERTIES_ARRAY
#undef INSERT_PROPERTY
#undef REMOVE_PROPERTY