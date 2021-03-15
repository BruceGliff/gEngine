#pragma once

#include <unordered_map>
#include <memory>

#include "../manager/Entity.h"
#include "../actor/actor.h"
#include "../debug/debug.h"
#include "../geometry/geometry_base.h"
#include "gismo/grid.h"

namespace Actor
{
    class actor;
}

namespace Scene
{
// Class that containt all resources in the scene and Process in loop
// All objects in scene must have Entity to be accessable directly by it
// We assume, that scene occupies and releases all resources pass to it
class Scene final
{
    Grid grid;
    std::unordered_map<Resources::Entity, std::shared_ptr<Actor::actor>> scene;
    // TODO make light seperate

    typedef std::unordered_map<Resources::Entity, std::shared_ptr<Actor::actor>>::iterator iterator;
    typedef std::unordered_map<Resources::Entity, std::shared_ptr<Actor::actor>>::const_iterator const_iterator;

public:
    Scene() = default;
    Scene(Scene const&)				= delete;
    Scene(Scene&&)					= delete;
    Scene& operator= (Scene const&) = delete;
    Scene& operator= (Scene&&)		= delete;

    void Process()
    {
        Geometry::Transformation tr{};
        grid.Draw(tr);
        for (auto && x : scene)
            x.second->Process(tr);        
    }


    // Spawn an object at scene.
    // Return nullptr, if object cannot be spawned
    // Return shared_ptr of created object
    template<typename T, typename ... Args>
    std::shared_ptr<T> Spawn(Args && ... args)
    {
        std::shared_ptr<T> p = std::make_shared<T>(std::forward<Args>(args) ...);
        std::shared_ptr<Actor::actor> pA = std::dynamic_pointer_cast<Actor::actor>(p);
        if (pA.get() == nullptr)
        {
            gWARNING(std::string{"Type is not an actor: "} + typeid(T).name());
            return nullptr;
        }

        scene[pA->GetEntity()] = std::move(pA);

        return p;
    }

    // Attach already created object to scene
    // Resource occupation comes to scene
    // If somehow object is already in scene, then return nullptr
    // Return shared_ptr of created object, or nullptr is object is not spawnable
    template<typename T, typename NoRefT = typename std::remove_reference<T>::type>
    std::shared_ptr<NoRefT> Attach(T && obj)
    {
        std::shared_ptr<NoRefT> p = std::make_shared<NoRefT>( std::move(obj) );
        std::shared_ptr<Actor::actor> pA = std::dynamic_pointer_cast<Actor::actor>(p);
        if (pA.get() == nullptr)
        {
            gWARNING(std::string{"Type is not an actor: "} + typeid(T).name());
            return nullptr;
        }

        auto && it = scene.find(pA->GetEntity());
        if (it != scene.end())
        {
            gWARNING(std::string{"This is not suppose to happen: Object already in scene. id: "} + std::to_string(pA->GetEntityID()));
            return nullptr;
        }
        
        // scene[pA->GetEntity] does copy of entity
        scene[pA->GetEntity()] = std::move(pA);

        return p;
    }

    // TODO think about GetActor throws an exctention.
    // Return shared_ptr of actor with given Entity(id) or nullptr if it is not found
    std::shared_ptr<Actor::actor> GetActor(Resources::Entity const & en) const noexcept
    {
        auto && it = scene.find(en);
        if (it == scene.end())
        {
            gWARNING(std::string{"Attempt to get unexisted actor id: "} + std::to_string(en.GetEntityID()));
            return nullptr;
        }

        return it->second;
    }
    // Return shared_ptr of type T with given Entity(id) or nullptr if it is not found or it cannot be type T
    template <typename T>
    std::shared_ptr<T> GetActor(Resources::Entity const & en) const noexcept
    {
        auto && it = scene.find(en);
        if (it == scene.end())
        {
            gWARNING(std::string{"Attempt to get unexisted actor id: "} + std::to_string(en.GetEntityID()));
            return nullptr;
        }

        return std::dynamic_pointer_cast<T>(it->second);
    }

    // Return shared_ptr of actor with given Entity(id) or nullptr if it is not found
    std::shared_ptr<Actor::actor> operator[](Resources::Entity const & en) const noexcept
    {
        return GetActor(en);
    }

    iterator begin() noexcept
    {
        return scene.begin();
    }
    iterator end() noexcept
    {
        return scene.end();
    }
    const_iterator begin() const noexcept
    {
        return scene.begin();
    }
    const_iterator end() const noexcept
    {
        return scene.end();
    }

};

}
