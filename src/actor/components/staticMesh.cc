#include "staticMesh.h"

#include "model/model3D.h"
#include "process/global.h"
#include "camera.h"
#include "../actor.h"
#include "renderer/ShaderProgram.h"
#include "geometry/geometry_base.h"
#include "manager/ResourceManager.h"

#include "glad/glad.h"

using namepace Component;

StaticMesh::StaticMesh(std::string const& name)
    : model{GLOBAL::GetResManager().getModel(name)} {

}

StaticMesh::StaticMesh(Model::IModel * model)
    : model{model} {

}

StaticMesh::~StaticMesh() {

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
    model->Draw(*shader);
}