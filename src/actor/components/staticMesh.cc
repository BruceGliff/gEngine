#include "staticMesh.h"
#include "model/mesh_base.h"
#include "process/global.h"
#include "camera.h"
#include "../actor.h"
#include "renderer/ShaderProgram.h"
#include "geometry/geometry_base.h"
#include "manager/ResourceManager.h"

#include "glad/glad.h"


Component::StaticMesh::StaticMesh(std::string const& name, std::filesystem::path const& relevantPath) :
    model{GLOBAL::GetResManager().loadModel<Model::Model3D>(name, relevantPath)}
{}

Component::StaticMesh::StaticMesh(std::string const& name) :
    model{GLOBAL::GetResManager().getModel(name)}
{}

Component::StaticMesh::StaticMesh(Model::IModel * model) :
    model{model}
{}

Component::StaticMesh::~StaticMesh()
{}

void Component::StaticMesh::Draw(Geometry::Transformation const & tr)
{
    shader->Use();
    // Optimize it! Probably for each draw iteration, pass this only once for each shader! Same in Grid.cc
    auto mainCam = GLOBAL::GetPlayer().GetComponentByName<Component::camera>("camera");
    shader->setMat4("view", mainCam->GetViewMatrix());
    shader->setMat4("projection", mainCam->GetProjectionMatrix());
    glm::mat4 const model_tr_matrix = glm::translate(glm::mat4{1.0f}, tr.displace);
    glm::mat4 const model_matrix = glm::scale(model_tr_matrix, tr.scale);
    shader->setMat4("model", model_matrix);
    model->Draw(*shader);
}