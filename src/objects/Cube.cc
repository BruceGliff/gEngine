#include "Cube.h"

#include "../process/global.h"
#include "../manager/ResourceManager.h"
#include "../model/primitives.h"
#include "../actor/components/staticMesh.h"

#include <string>

ACube::ACube() {
  NSResources::ResourcesManager & resMng = GLOBAL::GetResManager();

  NSModel::IModel * model = resMng.loadModel<NSModel::Cube>();
  NSComponent::StaticMesh * mesh = AttachComponent<NSComponent::StaticMesh>("cube_mesh", model);
  NSMaterial::Material * material = resMng.loadMaterial("cube_mat");
  material->Set<NSMaterial::Diffuse>(resMng.loadTexture("res/textures/container.png", std::string{"container_diffuse"}));
  material->Set<NSMaterial::Specular>(resMng.loadTexture("res/textures/container_specular.png", std::string{"container_specular"}));
  material->Set<NSMaterial::Ambient>(resMng.loadTexture(std::string{"container_diffuse"}));
  mesh->AttachMaterial(material);
  SetScale({0.1f, 0.1f, 0.1f});

  // TODO think how to set position properly
  NSComponent::PointLight * light = AttachComponent<NSComponent::PointLight>("light", glm::vec3{1.f, 1.f, 1.f});
  light->SetAmbient({0.1f, 0.1f, 0.1f});
  light->SetDiffuse({0.8f, 0.8f, 0.8f});
  light->SetSpecular({0.5f, 0.5f, 0.5f});

  NSComponent::PointLight * light2 = AttachComponent<NSComponent::PointLight>("light2", glm::vec3{-1.f, -1.f, -1.f});
  light2->SetAmbient({0.1f, 0.f, 0.f});
  light2->SetDiffuse({0.8f, 0.f, 0.f});
  light2->SetSpecular({0.5f, 0.5f, 0.5f});
}