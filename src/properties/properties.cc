#include "properties.h"

#include "process/global.h"
#include "manager/ResourceManager.h"

Property::IPlaceable::IPlaceable() : anchor_position{ 0.f, 0.f, 0.f }
{}

Property::IPlaceable::IPlaceable(glm::vec3 const& pos) : anchor_position{pos}
{}
Property::IPlaceable::IPlaceable(IPlaceable && other) noexcept : 
    anchor_position{ std::move(other.anchor_position) }
{}

glm::vec3& Property::IPlaceable::GetPosition() noexcept
{
    return anchor_position;
}

glm::vec3 const& Property::IPlaceable::GetPosition() const noexcept
{
    return anchor_position;
}


Property::IMoveable & Property::IMoveable::SetPosition(glm::vec3 const& pos) noexcept
{
    anchor_position = pos;

    return *this;
}

Property::IMoveable::IMoveable(IMoveable&& other) noexcept :
    IPlaceable{std::move(other)}
{}

Property::IRotatable::IRotatable(IRotatable&& other) noexcept :
    rotator{ std::move(other.rotator) }
{}

glm::vec3& Property::IRotatable::GetRotation() noexcept
{
    return rotator;
}
glm::vec3 const& Property::IRotatable::GetRotation() const noexcept
{
    return rotator;
}

Property::IScalable::IScalable(IScalable&& other) noexcept :
    scale{std::move(other.scale)}
{}

glm::vec3& Property::IScalable::GetScale() noexcept
{
    return scale;
}
glm::vec3 const& Property::IScalable::GetScale() const noexcept
{
    return scale;
}

Property::IScalable & Property::IScalable::SetScale(glm::vec3 const& sc) noexcept
{
    scale = sc;
    return *this;
}

Property::IDrawable::IDrawable()
{
    // Be default All drawable shaders load already created shaders. So DefaultObjShader HAS to be created!
    auto & Mgr = GLOBAL::GetResManager();
    borderShader = Mgr.loadShaders("boarderShader", "res/shaders/stencil/border.vs", "res/shaders/stencil/border.fs");
    shader = Mgr.getShaderProgram("DefaultObjShader");
    if (!shader)
        gERROR("Loading unexisted DefaultObjShader! It has to be created first");
}

Property::IDrawable::IDrawable(Renderer::ShaderProgram * sp)
{
    auto & Mgr = GLOBAL::GetResManager();
    borderShader = Mgr.loadShaders("boarderShader", "res/shaders/stencil/border.vs", "res/shaders/stencil/border.fs");
    shader = sp;
}

void Property::IDrawable::SetShaderProgram(Renderer::ShaderProgram * sp) noexcept
{
    shader = sp;
}
