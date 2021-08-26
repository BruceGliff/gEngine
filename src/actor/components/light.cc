#include "light.h"

#include "../../debug/debug.h"

#include "../../renderer/ShaderProgram.h"
#include "../../process/global.h"
#include "../../scene/scene.h"

#include <string>
#include <typeinfo>

using namespace NSComponent;


void ILight::PassColorToShader(char const * LightName, NSRenderer::ShaderProgram const & Shader) const {
    std::string prefix {std::string{LightName}.append(".colors.")};
    Shader.setVec3(std::string{prefix + "ambient"}.c_str(), m_Ambient);
    Shader.setVec3(std::string{prefix + "diffuse"}.c_str(), m_Diffuse);
    Shader.setVec3(std::string{prefix + "specular"}.c_str(), m_Specular);
}

ILight& ILight::SetAmbient(glm::vec3 const & Ambient) noexcept {
    m_Ambient = Ambient;
    return *this;
}
ILight& ILight::SetDiffuse(glm::vec3 const & Diffuse) noexcept {
    m_Diffuse = Diffuse;
    return *this;
}
ILight& ILight::SetSpecular(glm::vec3 const & Specular) noexcept {
    m_Specular = Specular;
    return *this;
}

GlobalLight::GlobalLight(glm::vec3 const & Direction) noexcept
    : m_Direction { glm::normalize(Direction)} {
}

void GlobalLight::Procces(NSRenderer::ShaderProgram const & Shader) const {
    Shader.Use();
    Shader.setVec3("GlobalLight.direction", m_Direction);
    PassColorToShader("GlobalLight", Shader);
}

GlobalLight& GlobalLight::SetDirection(glm::vec3 const & Direction) noexcept {
    m_Direction = glm::normalize(Direction);
    return *this;
}

PointLight::PointLight(glm::vec3 const & Position) noexcept {
    SetPosition(Position);
}

void PointLight::Procces(NSRenderer::ShaderProgram const & Shader) const {
    unsigned LightID = GLOBAL::GetScene().GetLightID() - 1;

    Shader.Use();
    std::string const LightIndx = "PointLights[" + std::to_string(LightID) + "]";
    Shader.setVec3(std::string{LightIndx + ".position"}.c_str(), GetPosition());
    Shader.setFloat(std::string{LightIndx + ".constant"}.c_str(), 1.0f);
    Shader.setFloat(std::string{LightIndx + ".linear"}.c_str(), 0.09f);
    Shader.setFloat(std::string{LightIndx + ".quadratic"}.c_str(), 0.032f);
    PassColorToShader(LightIndx.c_str(), Shader);
}
