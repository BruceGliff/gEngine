#include "sun.h"

#include "../process/global.h"
#include "../manager/ResourceManager.h"
#include "../actor/components/light.h"

#include <string>

ALSun::ALSun() {
  NSResources::ResourcesManager & resMng = GLOBAL::GetResManager();

  NSComponent::GlobalLight * light = AttachComponent<NSComponent::GlobalLight>("global_light", glm::vec3{-1.f, -1.f, -1.f});
  light->SetAmbient({0.1f, 0.1f, 0.1f});
  light->SetDiffuse({0.8f, 0.8f, 0.8f});
  light->SetSpecular({0.5f, 0.5f, 0.5f});
}