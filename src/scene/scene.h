#pragma once

#include <unordered_map>

#include "actor/actor.h"
#include "manager/Entity.h"
#include "gismo/grid.h"

namespace Scene
{
// Class that containt all resources in the scene and Process in loop
// All objects in scene must have Entity to be accessable directly by it
// We assume, that scene occupies and releases all resources passed to it
class Scene final
{
    Grid grid;
    // TODO make maped container to scene which represent sorted objects
    std::unordered_map<Resources::Entity, std::unique_ptr<Actor::actor>> scene;
    // TODO make light seperate
    // TODO separate transparent objects and opaque to sort transparent from furthes to nearest

    typedef std::unordered_map<Resources::Entity, std::unique_ptr<Actor::actor>>::iterator iterator;
    typedef std::unordered_map<Resources::Entity, std::unique_ptr<Actor::actor>>::const_iterator const_iterator;

public:
    Scene() = default;
    Scene(Scene const&)				= delete;
    Scene(Scene&&)					= delete;
    Scene& operator= (Scene const&) = delete;
    Scene& operator= (Scene&&)		= delete;

    // Process all objects in scene
    void Process();


    // Spawn an object at scene.
    // Return nullptr, if object cannot be spawned
    // Return ptr of created object
    template<typename T, typename ... Args>
    T * Spawn(Args && ... args);

    // Attach already created object to scene
    // Resource occupation comes to scene
    // If somehow object is already in scene, then return nullptr
    // Return ptr of created object, or nullptr is object is not spawnable
    template<typename T, typename NoRefT = typename std::remove_reference<T>::type>
    NoRefT * Attach(T && obj);

    // TODO think about GetActor throws an exctention.
    // Return ptr of actor with given Entity(id) or nullptr if it is not found
    Actor::actor * GetActor(Resources::Entity const & en) const noexcept;

    // Return ptr of type T with given Entity(id) or nullptr if it is not found or it cannot be type T
    template <typename T>
    T * GetActor(Resources::Entity const & en) const noexcept;

    // Return ptr of actor with given Entity(id) or nullptr if it is not found
    Actor::actor * operator[](Resources::Entity const & en) const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

};

}

#include "scene.hpp"
