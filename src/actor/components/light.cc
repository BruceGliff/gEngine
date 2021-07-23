#include "light.h"

#include "../../renderer/ShaderProgram.h"

#include <string>

using namespace NSComponent;

void GlobalLight::Procces(NSRenderer::ShaderProgram const & Shader) const {
    Shader.Use();
    Shader.setVec3("GlobalLight.direction", m_Direction);
    Shader.setVec3("GlobalLight.colors.ambient", m_Direction);
    Shader.setVec3("GlobalLight.colors.diffuse", m_Direction);
    Shader.setVec3("GlobalLight.colors.specular", m_Direction);
}

GlobalLight& GlobalLight::SetDirection(glm::vec3 const & Direction) noexcept {
    m_Direction = Direction;
}

