#include "backpack.h"

#include "../process/global.h"
#include "../manager/ResourceManager.h"
#include "../model/model3D.h"
#include "../actor/components/staticMesh.h"

#include <string>

ABackpack::ABackpack() {
  NSResources::ResourcesManager & resMng = GLOBAL::GetResManager();

  NSModel::IModel * model = resMng.loadModel<NSModel::Model3D>("backpack", "res/models/backpack/backpack.obj");
  NSComponent::StaticMesh * mesh = AttachComponent<NSComponent::StaticMesh>("backpack_mesh", model);
  NSMaterial::Material * material = resMng.loadMaterial("backpack_mat");
  material->Set<NSMaterial::Diffuse>(resMng.loadTexture("res/models/backpack/diffuse.jpg", std::string{"backpack_diffuse"}));
  material->Set<NSMaterial::Specular>(resMng.loadTexture("res/models/backpack/specular.jpg", std::string{"backpack_specular"}));
  material->Set<NSMaterial::Ambient>(resMng.loadTexture(std::string{"backpack_diffuse"}));

  mesh->AttachMaterial(material);
}