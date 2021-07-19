#pragma once

#include <unordered_map>
#include <vector>

#include "actor/actor.h"
#include "manager/Entity.h"
#include "gismo/grid.h"

namespace NSScene {
// Class that containt all resources in the scene and Process in loop
// All objects in scene must have Entity to be accessable directly by it
// We assume, that scene occupies and releases all resources passed to it
class Scene final {
    Grid grid;
    // TODO make maped container to scene which represent sorted objects
    std::unordered_map<NSResources::Entity, std::unique_ptr<NSActor::actor>> scene;
    // TODO make light seperate
    // TODO separate transparent objects and opaque to sort transparent from furthes to nearest

    typedef std::unordered_map<NSResources::Entity, std::unique_ptr<NSActor::actor>>::iterator iterator;
    typedef std::unordered_map<NSResources::Entity, std::unique_ptr<NSActor::actor>>::const_iterator const_iterator;

    int const sceneDefSize = 100; // default there are max 100 objects in scene to avoid rallocations
    std::vector<const_iterator> blendedObjects;

public:
    Scene();
    Scene(Scene const&)                = delete;
    Scene(Scene&&)                    = delete;
    Scene& operator= (Scene const&) = delete;
    Scene& operator= (Scene&&)        = delete;

    // Process all objects in scene
    void Process();

    // TODO as I don't have deletions from scene blendedObjects are increased in
    // Spawn and Attach methods. As there will be deletions, have to think how to
    // delete from blendedObjects.

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
    NSActor::actor * GetActor(NSResources::Entity const & en) const noexcept;

    // Return ptr of type T with given Entity(id) or nullptr if it is not found or it cannot be type T
    template <typename T>
    T * GetActor(NSResources::Entity const & en) const noexcept;

    // Return ptr of actor with given Entity(id) or nullptr if it is not found
    NSActor::actor * operator[](NSResources::Entity const & en) const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

};

} //namespace NSScene
#include "scene.hpp"
