#include "scene.h"

#include <algorithm>
#include <glm/gtx/norm.hpp>

#include "geometry/geometry_base.h"
#include "../properties/properties.h"
#include "../actor/components/light.h"
#include "../renderer/ShaderProgram.h"

using namespace NSScene;

Scene::Scene() {
    blendedObjects.reserve(sceneDefSize);
}

void Scene::Process() {
    NSGeometry::Transformation tr{};
    grid.Draw(tr);

    auto & camPos = GLOBAL::GetPlayer().GetPosition();

    // may be apply more sutable sort algorithm for sort weak changed objects
    std::sort(blendedObjects.begin(), blendedObjects.end(), 
                [&camPos](const_iterator const & a, const_iterator const & b) {
                    return  glm::length2(a->second->GetPosition() - camPos) > 
                            glm::length2(b->second->GetPosition() - camPos);
                });
    for (auto && x : blendedObjects) {
        NSActor::actor & pA = *x->second.get();
        if (pA.IsDrawable())
            std::for_each(pA.drawable_begin(), pA.drawable_end(), [this](NSProperty::IProcessable * proc) {
                if (NSProperty::IDrawable * Drawable = dynamic_cast<NSProperty::IDrawable *>(proc)) // TODO static_cast?
                    if (NSRenderer::ShaderProgram * Shader = Drawable->GetShaderProgram())
                        for (auto const & [key, light] : lightsInScene)
                            light->Procces(*Shader);
                else 
                    gERROR("Not suppose to happen! not Drawable in DrawableList");

            });
        x->second->Process(tr);
    }
}

NSActor::actor * Scene::GetActor(NSResources::Entity const & en) const noexcept {
    auto && it = scene.find(en);
    if (it == scene.end()) {
        gWARNING(std::string{"Attempt to get unexisted actor id: "} + std::to_string(en.GetEntityID()));
        return nullptr;
    }

    return it->second.get();
}

NSActor::actor * Scene::operator[](NSResources::Entity const & en) const noexcept {
    return GetActor(en);
}

bool Scene::emplaceActor(NSActor::actor * pA) {
    auto && it = scene.find(pA->GetEntity());
    if (it != scene.end()) {
        gWARNING(std::string{"This is not suppose to happen: Object already in scene. id: "} + std::to_string(pA->GetEntityID()));
        return false;
    }
    std::for_each(pA->lights_begin(), pA->lights_end(), [this](NSComponent::ILight * light) {
        lightsInScene.emplace(light->GetEntity(), light);
    });
    // TODO make insertion in anothe way. With check return value
    auto spawned = scene.emplace(pA->GetEntity(), pA);
    blendedObjects.push_back(spawned.first);

    return true;
}