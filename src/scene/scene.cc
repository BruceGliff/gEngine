#include "scene.h"

#include <algorithm>
#include <glm/gtx/norm.hpp>

#include "geometry/geometry_base.h"

Scene::Scene::Scene() {
    blendedObjects.reserve(sceneDefSize);
}

void Scene::Scene::Process()
{
    Geometry::Transformation tr{};
    grid.Draw(tr);

    auto & camPos = GLOBAL::GetPlayer().GetPosition();

    // may be apply more sutable sort algorithm for sort weak changed objects
    std::sort(blendedObjects.begin(), blendedObjects.end(), 
                [&camPos](const_iterator const & a, const_iterator const & b)
                {
                    return  glm::length2(a->second->GetPosition() - camPos) > 
                            glm::length2(b->second->GetPosition() - camPos);
                });
    for (auto && x : blendedObjects)
        x->second->Process(tr);

}

Actor::actor * Scene::Scene::GetActor(Resources::Entity const & en) const noexcept
{
    auto && it = scene.find(en);
    if (it == scene.end())
    {
        gWARNING(std::string{"Attempt to get unexisted actor id: "} + std::to_string(en.GetEntityID()));
        return nullptr;
    }

    return it->second.get();
}

Actor::actor * Scene::Scene::operator[](Resources::Entity const & en) const noexcept
{
    return GetActor(en);
}

Scene::Scene::iterator Scene::Scene::begin() noexcept
{
    return scene.begin();
}
Scene::Scene::iterator Scene::Scene::end() noexcept
{
    return scene.end();
}
Scene::Scene::const_iterator Scene::Scene::begin() const noexcept
{
    return scene.begin();
}
Scene::Scene::const_iterator Scene::Scene::end() const noexcept
{
    return scene.end();
}