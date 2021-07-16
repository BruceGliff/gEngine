#include "staticMesh.h"

#include "../../model/model3D.h"
#include "../../process/global.h"
#include "camera.h"
#include "../actor.h"
#include "../../renderer/ShaderProgram.h"
#include "../../geometry/geometry_base.h"
#include "../../manager/ResourceManager.h"
#include "../../Material/material.h"

#include <glad/glad.h>

using namespace Component;

StaticMesh::StaticMesh(std::string const& name)
    : m_Model{GLOBAL::GetResManager().getModel(name)} {}

StaticMesh::StaticMesh(Model::IModel * model)
    : m_Model{model} {}

StaticMesh::~StaticMesh() {}

Material::Material * StaticMesh::AttachMaterial(Material::Material * material) noexcept {
    m_Material = material;
}

void StaticMesh::Draw(Geometry::Transformation const & tr) {
    shader->Use();
    // Optimize it! Probably for each draw iteration, pass this only once for each shader! Same in Grid.cc
    auto mainCam = GLOBAL::GetPlayer().GetComponentByName<Component::camera>("camera"); // bad impl: what if i've named camera "watcher"?
    shader->setMat4("view", mainCam->GetViewMatrix());
    shader->setMat4("projection", mainCam->GetProjectionMatrix());
    glm::mat4 const model_tr_matrix = glm::translate(glm::mat4{1.0f}, tr.displace);
    glm::mat4 const model_matrix = glm::scale(model_tr_matrix, tr.scale);
    shader->setMat4("model", model_matrix);
    if (m_Material) {
        m_Material->process();
    } else gWARNING("Material is not attached");
    m_Model->Draw(*shader);
}