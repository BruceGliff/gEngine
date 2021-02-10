#pragma once

#include <unordered_map>
#include <memory>

#include "../manager/Entity.h"
#include "../actor/actor.h"
#include "../debug/debug.h"

namespace Actor
{
    class actor;
}

namespace Scene
{
class Scene final
{
    std::unordered_map<Resources::Entity, std::shared_ptr<Actor::actor>> scene;
    // TODO make light seperate

public:
    Scene() = default;
    Scene(Scene const&)				= delete;
    Scene(Scene&&)					= delete;
    Scene& operator= (Scene const&) = delete;
    Scene& operator= (Scene&&)		= delete;

    // Spawn an object at scene
    template<typename T, typename ... Args>
    std::shared_ptr<Actor::actor> Spawn(Args && ... args)
    {
        std::shared_ptr<T> p{std::forward<Args>(args) ...};
        std::shared_ptr<Actor::actor> pA = std::dynamic_pointer_cast<Actor::actor>(p);
        if (pA.get() == nullptr)
        {
            gWARNING("Type is not an actor!");
            return nullptr;
        }

        return scene[pA->GetEntity()] = std::move(pA);
    }

    // Attach already created object to scene
    // Resource occupation comes to scene
    // If somehow object is already in scene, then do nothing
    template<typename T>
    std::shared_ptr<Actor::actor> Attach(T && obj)
    {
        std::shared_ptr<T> p = std::make_shared<T>(std::move(obj));
        std::shared_ptr<Actor::actor> pA = std::dynamic_pointer_cast<Actor::actor>(p);
        if (pA.get() == nullptr)
        {
            gWARNING("Type is not an actor!");
            return nullptr;
        }

        auto && it = scene.find(pA->GetEntity())
        if (it != scene.end())
        {
            gWARNING("THIS IS NOT SUPPOSE TO HAPPEN!!");
            return nullptr;
        }
        return scene[pA->GetEntity()] = std::move(pA);
    }

    std::shared_ptr<Actor::actor> GetActor(Resources::Entity const & en) const noexcept
    {
        auto && it = scene.find(en);
        if (it != scene.end())
        {
            gWARNING("Attempt to get unexisted actor");
            return nullptr;
        }

        return it->second;
    }

    std::shared_ptr<Actor::actor> operator[](Resources::Entity const & en) const noexcept
    {
        return GetActor(en);
    }


};


}