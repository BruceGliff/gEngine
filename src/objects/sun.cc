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

void ALSun::Process(NSGeometry::Transformation const & tr) {
  float const speed = 0.01f;
  static unsigned frame = 0; // TODO move frame into function params as delay

  // light will be proccesed automaticali in actor
  NSComponent::GlobalLight * light = GetComponentByName<NSComponent::GlobalLight>("global_light");

  float const x = std::cos(speed * frame++);
  float const z = std::sin(speed * frame++);

  light->SetDirection({x, -1.f, z});

  actor::Process(tr);
}