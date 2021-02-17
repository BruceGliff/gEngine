#include "staticMesh.h"
#include "../../model/mesh_base.h"
#include "../../process/global.h"
#include "camera.h"
#include "../actor.h"
#include "../../renderer/ShaderProgram.h"
#include "../../geometry/geometry_base.h"

Component::StaticMesh::StaticMesh(std::filesystem::path const& path)
{
    model = new Model::Model{path};
}

Component::StaticMesh::~StaticMesh()
{
    delete model;
}

void Component::StaticMesh::Draw(Renderer::ShaderProgram const & sp, Geometry::Transformation const & tr)
{
    auto mainCam = GLOBAL::GetPlayer().GetComponentByName<Component::camera>("camera");
    sp.setMat4("view", mainCam->GetViewMatrix());
    sp.setMat4("projection", mainCam->GetProjectionMatrix());

    glm::mat4 model_matrix = glm::mat4(1.0f);
    model_matrix = glm::translate(model_matrix, tr.displace); // translate it down so it's at the center of the scene
    model_matrix = glm::scale(model_matrix, tr.scale);	    // it's a bit too big for our scene, so scale it down
    sp.setMat4("model", model_matrix);
    
    model->Draw(sp);
}