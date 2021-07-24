#include "Cube.h"

#include "../process/global.h"
#include "../manager/ResourceManager.h"
#include "../model/model3D.h"
#include "../actor/components/staticMesh.h"

#include <string>

ACube::ACube() {
  NSResources::ResourcesManager & resMng = GLOBAL::GetResManager();

  NSModel::IModel * model = resMng.loadModel<NSModel::Model3D>("cube", "res/models/primitives/Cube.obj");
  NSComponent::StaticMesh * mesh = AttachComponent<NSComponent::StaticMesh>("cube_mesh", model);
  NSMaterial::Material * material = resMng.loadMaterial("cube_mat");
  material->Set<NSMaterial::Diffuse>(resMng.loadTexture("res/textures/container.png", std::string{"container_diffuse"}));
  material->Set<NSMaterial::Specular>(resMng.loadTexture("res/textures/container_specular.png", std::string{"container_specular"}));
  material->Set<NSMaterial::Ambient>(resMng.loadTexture(std::string{"container_diffuse"}));
  mesh->AttachMaterial(material);
  SetScale({0.1f, 0.1f, 0.1f});
}