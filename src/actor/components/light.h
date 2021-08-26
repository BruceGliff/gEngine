#pragma once

#include "component_base.h"

#include "../../manager/Entity.h"
#include "../../properties/properties.h"

#include <glm/vec3.hpp>


namespace NSRenderer {
    class ShaderProgram;
} //namespace NSRenderer


namespace NSComponent {

class ILight
    : public component_base
    , public NSResources::Entity {
    glm::vec3 m_Ambient {1.f};
    glm::vec3 m_Diffuse {1.f};
    glm::vec3 m_Specular {1.f};
protected:
    void PassColorToShader(char const * LightName, NSRenderer::ShaderProgram const & Shader) const;
public:
    ILight() = default;
    ILight(ILight &&) = delete;
    ILight(ILight const &) = delete;
    ILight& operator=(ILight const &) = delete;
    ILight& operator=(ILight &&) = delete;


    virtual void Procces(NSRenderer::ShaderProgram const &) const = 0;
    ILight& SetAmbient(glm::vec3 const & Ambient) noexcept;
    ILight& SetDiffuse(glm::vec3 const & Diffuse) noexcept;
    ILight& SetSpecular(glm::vec3 const & Specular) noexcept;
};

class GlobalLight
    : public ILight {
    glm::vec3 m_Direction {1.f};
public:
    GlobalLight(glm::vec3 const & Direction) noexcept;
    
    void Procces(NSRenderer::ShaderProgram const & Shader) const override;

    GlobalLight& SetDirection(glm::vec3 const & Direction) noexcept;
};

class PointLight
    : public ILight
    , public NSProperty::IMoveable {
public:
    PointLight(glm::vec3 const & Position) noexcept;

    void Procces(NSRenderer::ShaderProgram const & Shader) const override;
};

} //namespace NSComponent;