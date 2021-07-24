#include "properties.h"

#include "process/global.h"
#include "manager/ResourceManager.h"

using namespace NSProperty;

IPlaceable::IPlaceable()
    : anchor_position{ 0.f, 0.f, 0.f } {}

IPlaceable::IPlaceable(glm::vec3 const& pos)
    : anchor_position{pos} {}
IPlaceable::IPlaceable(IPlaceable && other) noexcept
    : anchor_position{ std::move(other.anchor_position) } {}

glm::vec3& IPlaceable::GetPosition() noexcept {
    return anchor_position;
}

glm::vec3 const& IPlaceable::GetPosition() const noexcept {
    return anchor_position;
}


IMoveable & IMoveable::SetPosition(glm::vec3 const& pos) noexcept {
    anchor_position = pos;
    return *this;
}

IMoveable::IMoveable(IMoveable&& other) noexcept
    : IPlaceable{std::move(other)} {}

IRotatable::IRotatable(IRotatable&& other) noexcept
    : rotator{ std::move(other.rotator) } {}

glm::vec3& IRotatable::GetRotation() noexcept {
    return rotator;
}
glm::vec3 const& IRotatable::GetRotation() const noexcept {
    return rotator;
}

IScalable::IScalable(IScalable&& other) noexcept
    : scale{std::move(other.scale)} {}

glm::vec3& IScalable::GetScale() noexcept {
    return scale;
}
glm::vec3 const& IScalable::GetScale() const noexcept {
    return scale;
}

IScalable & IScalable::SetScale(glm::vec3 const& sc) noexcept {
    scale = sc;
    return *this;
}

IDrawable::IDrawable() {
    // Be default All drawable shaders load already created shaders. So DefaultObjShader HAS to be created!
    auto & Mgr = GLOBAL::GetResManager();
    borderShader = Mgr.loadShaders("boarderShader", "res/shaders/stencil/border.vs", "res/shaders/stencil/border.fs");
    shader = Mgr.getShaderProgram("DefaultObjShader");
    if (!shader)
        gERROR("Loading unexisted DefaultObjShader! It has to be created first");
}

IDrawable::IDrawable(NSRenderer::ShaderProgram * sp) {
    auto & Mgr = GLOBAL::GetResManager();
    borderShader = Mgr.loadShaders("boarderShader", "res/shaders/stencil/border.vs", "res/shaders/stencil/border.fs");
    shader = sp;
}

void IDrawable::SetShaderProgram(NSRenderer::ShaderProgram * sp) noexcept {
    shader = sp;
}
NSRenderer::ShaderProgram * IDrawable::GetShaderProgram() const noexcept  {
    if (!shader)
        gWARNING("Getting null shader");
    return shader;
}
