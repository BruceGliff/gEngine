#pragma once

#include <glm/vec3.hpp>

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
    class IProcessable {
    public:
        virtual ~IProcessable() {};
    };

    class IPlaceable
    {
    protected:
        glm::vec3 anchor_position;
    public:
        IPlaceable();
        IPlaceable(glm::vec3 const& pos);
        IPlaceable(IPlaceable const&)                = delete;
        IPlaceable(IPlaceable&& other) noexcept;
        IPlaceable& operator= (IPlaceable const&)   = delete;
        IPlaceable& operator= (IPlaceable&&)        = delete;

        glm::vec3& GetPosition() noexcept;
        glm::vec3 const& GetPosition() const noexcept;

        virtual ~IPlaceable() {};
    };

    class IMoveable : public IPlaceable
    {
    public:
        IMoveable & SetPosition(glm::vec3 const& pos) noexcept;

        IMoveable() = default;
        IMoveable(IMoveable const&)                = delete;
        IMoveable(IMoveable&& other) noexcept;
        IMoveable& operator= (IMoveable const&)    = delete;
        IMoveable& operator= (IMoveable&&)        = delete;

        virtual ~IMoveable() {};
    };

    class IDrawable : public IProcessable
    {
    protected:
        Renderer::ShaderProgram * borderShader;    
        Renderer::ShaderProgram * shader;
    public:
        virtual void Draw(Geometry::Transformation const &) {};

        IDrawable();
        IDrawable(Renderer::ShaderProgram * sp);
        IDrawable(IDrawable const &) = delete;
        IDrawable(IDrawable &&) = delete;
        IDrawable& operator= (IDrawable const &)  =delete;
        IDrawable& operator=(IDrawable &&) = delete;

        // Assign to each drawable object shader program what is responsible for drawing
        void SetShaderProgram(Renderer::ShaderProgram * sp) noexcept;

        virtual ~IDrawable(){}
    };

    // TODO fo it
    class IRotatable
    {
        glm::vec3 rotator = {0.f, 0.f, 0.f};
    public:
        IRotatable() = default;
        IRotatable(IRotatable const&)                = delete;
        IRotatable(IRotatable&& other) noexcept;
        IRotatable& operator= (IRotatable const&)   = delete;
        IRotatable& operator= (IRotatable&&)        = delete;

        glm::vec3& GetRotation() noexcept;
        glm::vec3 const& GetRotation() const noexcept;

        virtual ~IRotatable() {};
    };

    class IScalable
    {
        glm::vec3 scale = {1.f, 1.f, 1.f};
    public:
        IScalable() = default;
        IScalable(IScalable const&)                = delete;
        IScalable(IScalable&& other) noexcept;
        IScalable& operator= (IScalable const&) = delete;
        IScalable& operator= (IScalable&&)        = delete;

        glm::vec3& GetScale() noexcept;
        glm::vec3 const& GetScale() const noexcept;

        IScalable & SetScale(glm::vec3 const& sc) noexcept;

        virtual ~IScalable() {};
    };

    class IPhysicaly
    {
    public:
        virtual ~IPhysicaly(){}
    };

    // This is used in objects which have component_base attached to them 
    class ICompound : public IProcessable
    {
    public:
        virtual void Process(Geometry::Transformation const&) {};
        virtual ~ICompound(){}
    };


}