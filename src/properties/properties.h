#pragma once

#include <glm/vec3.hpp>

namespace Renderer
{
    class ShaderProgram;
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
        virtual void Draw(Renderer::ShaderProgram const &) = 0;
        virtual ~IDrawable(){}

        IDrawable() = default;
        IDrawable(IDrawable const &) = delete;
        IDrawable(IDrawable &&) = delete;
        IDrawable& operator= (IDrawable const &)  =delete;
        IDrawable& operator=(IDrawable &&) = delete;
    };

    // TODO fo it
    class IRotatable
    {};

	class IScalable
	{};

	class IPhysicaly
	{};


}