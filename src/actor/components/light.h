#pragma once

#include "component_base.h"

#include "../../manager/Entity.h"

#include <glm/vec3.hpp>


namespace NSRenderer {
    class ShaderProgram;
} //namespace NSRenderer


namespace NSComponent {

class ILight
    : public component_base
    , public NSResources::Entity {
public:
    ILight() = default;
    ILight(ILight &&) = delete;
    ILight(ILight const &) = delete;
    ILight& operator=(ILight const &) = delete;
    ILight& operator=(ILight &&) = delete;


    virtual void Procces(NSRenderer::ShaderProgram const &) const = 0;
    virtual ILight& SetAmbient(glm::vec3 const & ) noexcept = 0;
    virtual ILight& SetDiffuse(glm::vec3 const & ) noexcept = 0;
    virtual ILight& SetSpecular(glm::vec3 const & ) noexcept = 0;
};


#define OVERRIDE()                                                      \
void Procces(NSRenderer::ShaderProgram const & Shader) const override;  \
ILight& SetAmbient(glm::vec3 const & Ambient) noexcept override {       \
    m_Ambient = Ambient;                                                \
}                                                                       \
ILight& SetDiffuse(glm::vec3 const & Diffuse) noexcept override {       \
    m_Diffuse = Diffuse;                                                \
}                                                                       \
ILight& SetSpecular(glm::vec3 const & Specular) noexcept override {     \
    m_Specular = Specular;                                              \
}


class GlobalLight
    : public ILight {
    glm::vec3 m_Direction {1.f};
    glm::vec3 m_Ambient {1.f};
    glm::vec3 m_Diffuse {1.f};
    glm::vec3 m_Specular {1.f};
public:
    GlobalLight(glm::vec3 const & Direction) noexcept;
    GlobalLight(glm::vec3 && Direction) noexcept;

    // Process has to be defined in .cc
    OVERRIDE();

    GlobalLight& SetDirection(glm::vec3 const & Direction) noexcept;
};


#undef OVERRIDE
} //namespace NSComponent;