#include "staticMesh.h"
#include "../../model/mesh_base.h"
#include "../../process/global.h"
#include "camera.h"
#include "../actor.h"
#include "../../renderer/ShaderProgram.h"
#include "../../geometry/geometry_base.h"
#include "../../manager/ResourceManager.h"

#include "glad/glad.h"


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
    glStencilMask(0x00);
    shader->Use();
    auto mainCam = GLOBAL::GetPlayer().GetComponentByName<Component::camera>("camera");
    shader->setMat4("view", mainCam->GetViewMatrix());
    shader->setMat4("projection", mainCam->GetProjectionMatrix());
    glm::mat4 const model_tr_matrix = glm::translate(glm::mat4(1.0f), tr.displace); // translate it down so it's at the center of the scene

    glm::mat4 const model_matrix = glm::scale(model_tr_matrix, tr.scale);	    // it's a bit too big for our scene, so scale it down
    shader->setMat4("model", model_matrix);

    // insert here for normal drawing without stencil
    // model->Draw(*shader);
    // return;
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    model->Draw(*shader);

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);

    borderShader->Use();
    borderShader->setMat4("view", mainCam->GetViewMatrix());
    borderShader->setMat4("projection", mainCam->GetProjectionMatrix());
    borderShader->setMat4("model", model_matrix);
    model->Draw(*borderShader);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glEnable(GL_DEPTH_TEST);
}