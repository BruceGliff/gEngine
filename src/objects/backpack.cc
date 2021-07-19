#include "backpack.h"

#include "../process/global.h"
#include "../manager/ResourceManager.h"
#include "../model/model3D.h"
#include "../actor/components/staticMesh.h"

#include <string>

ABackpack::ABackpack() {
  Resources::ResourcesManager & resMng = GLOBAL::GetResManager();

  Model::IModel * model = resMng.loadModel<Model::Model3D>("backpack", "res/models/backpack/backpack.obj");
  Component::StaticMesh * mesh = AttachComponent<Component::StaticMesh>("backpack_mesh", model);
  MaterialNS::Material * material = resMng.loadMaterial("backpack_mat");
  material->Set<MaterialNS::Diffuse>(resMng.loadTexture("res/models/backpack/diffuse.jpg", std::string{"backpack_diffuse"}));
  material->Set<MaterialNS::Specular>(resMng.loadTexture("res/models/backpack/specular.jpg", std::string{"backpack_specular"}));
  
  mesh->AttachMaterial(material);
}