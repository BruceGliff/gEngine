#pragma once

#include <unordered_map>
#include <string>

#include <glm/vec3.hpp>

#include "components/component_base.h"

namespace Actor
{

	// TODO remove final
	// class that represent behavior of playable object
	// now it is just camera
	// TODO separate behavior to movement component, camera component and ...
	class actor_base
	{
	public:
		actor_base() noexcept {};
		actor_base(actor_base const&)				= delete;
		actor_base(actor_base &&)					= delete;
		actor_base& operator= (actor_base const&)	= delete;
		actor_base& operator= (actor_base &&)		= delete;

		virtual ~actor_base() {};
	};

	class placeable_obj : virtual public actor_base
	{
	protected:
		glm::vec3 anchor;
	public:
		placeable_obj();
		placeable_obj(glm::vec3 const& pos);
		placeable_obj(placeable_obj const&)				= delete;
		placeable_obj(placeable_obj&&)					= delete;
		placeable_obj& operator= (placeable_obj const&) = delete;
		placeable_obj& operator= (placeable_obj&&)		= delete;

		glm::vec3& GetPosition() noexcept;
		glm::vec3 const& GetPosition() const noexcept;

		virtual ~placeable_obj() {};

	};

	class moveable_obj : virtual public placeable_obj
	{
	public:
		void SetPosition(glm::vec3 const& pos);

		moveable_obj();
		moveable_obj(moveable_obj const&)				= delete;
		moveable_obj(moveable_obj&&)					= delete;
		moveable_obj& operator= (moveable_obj const&)	= delete;
		moveable_obj& operator= (moveable_obj&&)		= delete;

		virtual ~moveable_obj() {};
	};

	class component_attachable
	{
		std::unordered_map<std::string, Component::component_base *> components_map;

	public:
		component_attachable() {};
		component_attachable(component_attachable const&)				= delete;
		component_attachable(component_attachable&&)					= delete;
		component_attachable& operator= (component_attachable const&)	= delete;
		component_attachable& operator= (component_attachable&&)		= delete;

		// Attach component to object by name. 
		// Reattaches component if it already exists
		void attach_component(std::string const& comp_name, Component::component_base * component);
		Component::component_base * GetComponent(std::string const& comp_name) const;

		virtual ~component_attachable() {};
	};

	class actor : virtual public moveable_obj, public component_attachable
	{
	public:
		actor() {};
		actor(actor const&)				= delete;
		actor(actor&&)					= delete;
		actor& operator= (actor const&) = delete;
		actor& operator= (actor&&)		= delete;
	};




}