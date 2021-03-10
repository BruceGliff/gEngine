#include "staticMesh.h"
#include "../../model/mesh_base.h"
#include "../../process/global.h"
#include "camera.h"
#include "../actor.h"
#include "../../renderer/ShaderProgram.h"
#include "../../geometry/geometry_base.h"
#include "../../manager/ResourceManager.h"

Component::StaticMesh::StaticMesh(std::string const& name, std::filesystem::path const& relevantPath) :
    model{GLOBAL::GetResManager().loadModel(name, relevantPath)}
{}

Component::StaticMesh::StaticMesh(std::string const& name) :
    model{GLOBAL::GetResManager().getModel(name)}
{}

Component::StaticMesh::StaticMesh(std::shared_ptr<Model::Model> const& model) :
    model{model}
{}

Component::StaticMesh::~StaticMesh()
{}

void Component::StaticMesh::Draw(Geometry::Transformation const & tr)
{
    shader->Use();
    auto mainCam = GLOBAL::GetPlayer().GetComponentByName<Component::camera>("camera");
    shader->setMat4("view", mainCam->GetViewMatrix());
    shader->setMat4("projection", mainCam->GetProjectionMatrix());

    glm::mat4 model_matrix = glm::mat4(1.0f);
    model_matrix = glm::translate(model_matrix, tr.displace); // translate it down so it's at the center of the scene
    model_matrix = glm::scale(model_matrix, tr.scale);	    // it's a bit too big for our scene, so scale it down
    shader->setMat4("model", model_matrix);
    
    model->Draw(*shader);
}