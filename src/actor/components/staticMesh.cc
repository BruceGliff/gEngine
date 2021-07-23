#include "staticMesh.h"

#include "../../model/model3D.h"
#include "../../process/global.h"
#include "camera.h"
#include "../actor.h"
#include "../../renderer/ShaderProgram.h"
#include "../../geometry/geometry_base.h"
#include "../../manager/ResourceManager.h"
#include "../../material/material.h"

#include <glad/glad.h>

using namespace NSComponent;

StaticMesh::StaticMesh(std::string const& name)
    : m_Model{GLOBAL::GetResManager().getModel(name)} {}

StaticMesh::StaticMesh(NSModel::IModel * model)
    : m_Model{model} {}

StaticMesh::~StaticMesh() {}

NSMaterial::Material * StaticMesh::AttachMaterial(NSMaterial::Material * material) noexcept {
    return m_Material = material;
}

void StaticMesh::Draw(NSGeometry::Transformation const & tr) {
    shader->Use();
    // Optimize it! Probably for each draw iteration, pass this only once for each shader! Same in Grid.cc
    auto mainCam = GLOBAL::GetPlayer().GetComponentByName<NSComponent::camera>("camera"); // bad impl: what if i've named camera "watcher"?
    shader->setVec3("viewPos", mainCam->GetPosition());
    // std::cout << mainCam->GetPosition().x << ' ' << mainCam->GetPosition().y << "\n"; // TODO camera POS does no work!
    shader->setMat4("view", mainCam->GetViewMatrix());
    shader->setMat4("projection", mainCam->GetProjectionMatrix());
    glm::mat4 const model_tr_matrix = glm::translate(glm::mat4{1.0f}, tr.displace);
    glm::mat4 const model_matrix = glm::scale(model_tr_matrix, tr.scale);
    shader->setMat4("model", model_matrix);
    if (m_Material)
        m_Material->process(*shader);
    else gWARNING("Material is not attached");
    m_Model->Draw();
}