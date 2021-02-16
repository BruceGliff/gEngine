#pragma once

//#include <glm/vec3.hpp>
#include "../../external/glm/glm/vec3.hpp"

namespace Renderer
{
    class ShaderProgram;
}
namespace Geometry
{
	class Transformation;
}

namespace Property
{
    class IPlaceable
	{
	protected:
		glm::vec3 anchor_position;
	public:
		IPlaceable();
		IPlaceable(glm::vec3 const& pos);
		IPlaceable(IPlaceable const&)				= delete;
		IPlaceable(IPlaceable&&)					= delete;
		IPlaceable& operator= (IPlaceable const&)   = delete;
		IPlaceable& operator= (IPlaceable&&)		= delete;

		glm::vec3& GetPosition() noexcept;
		glm::vec3 const& GetPosition() const noexcept;

		virtual ~IPlaceable() {};
	};

    class IMoveable : public IPlaceable
	{
	public:
		IMoveable & SetPosition(glm::vec3 const& pos) noexcept;

		IMoveable() = default;
		IMoveable(IMoveable const&)				= delete;
		IMoveable(IMoveable&&)					= delete;
		IMoveable& operator= (IMoveable const&)	= delete;
		IMoveable& operator= (IMoveable&&)		= delete;

		virtual ~IMoveable() {};
	};

    class IDrawable
    {
    public:
        virtual void Draw(Renderer::ShaderProgram const &, Geometry::Transformation const &) = 0;

        IDrawable() = default;
        IDrawable(IDrawable const &) = delete;
        IDrawable(IDrawable &&) = delete;
        IDrawable& operator= (IDrawable const &)  =delete;
        IDrawable& operator=(IDrawable &&) = delete;

		virtual ~IDrawable(){}
    };

    // TODO fo it
    class IRotatable
    {
		glm::vec3 rotator = {0.f, 0.f, 0.f};
	public:
		IRotatable() {}
		IRotatable(glm::vec3 const& rot) 			= delete;
		IRotatable(IRotatable const&)				= delete;
		IRotatable(IRotatable&&)					= delete;
		IRotatable& operator= (IRotatable const&)   = delete;
		IRotatable& operator= (IRotatable&&)		= delete;

		glm::vec3& GetRotation() noexcept;
		glm::vec3 const& GetRotation() const noexcept;

		virtual ~IRotatable() {};
	};

	class IScalable
	{
		glm::vec3 scale = {1.f, 1.f, 1.f};
	public:
		IScalable() {}
		IScalable(glm::vec3 const& scal)		= delete;
		IScalable(IScalable const&)				= delete;
		IScalable(IScalable&&)					= delete;
		IScalable& operator= (IScalable const&) = delete;
		IScalable& operator= (IScalable&&)		= delete;

		glm::vec3& GetScale() noexcept;
		glm::vec3 const& GetScale() const noexcept;

		virtual ~IScalable() {};
	};

	class IPhysicaly
	{
	public:
		virtual ~IPhysicaly(){}
	};

	// This is used in objects which have component_base attached to them 
	class ICompound
	{
	public:
		virtual ~ICompound(){}
	};


}