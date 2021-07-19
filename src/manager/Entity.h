#pragma once

#include <functional>

namespace NSResources  {

// Entity is a most everything, placeable at scene: actors, and so on
// It is used to navigate in scene, as all objects will be mapped <entity, object>
class Entity {
    int id = -1;
    // Do id swaping. 
    void swap(Entity & entity)          noexcept;

public:
    Entity()                            noexcept;
    Entity(Entity const& entity)        noexcept;
    // move constuctor makes rval entity at rotten state
    Entity(Entity&& entity)             noexcept;
    Entity& operator =(Entity const&)   = delete;
    // move operator makes rval entity at rotten state
    Entity& operator=(Entity&& entity)  noexcept;

    // Return true, is there are the same entities
    bool operator==(Entity const& other) const noexcept;

    // Return ID of Entity
    int const & GetEntityID() const noexcept;

    // Return entity obj
    // To be possible do: map.find(actor());
    Entity & operator()() noexcept;
    Entity const & operator()() const noexcept;

    Entity & GetEntity() noexcept;
    Entity const & GetEntity() const noexcept;

    virtual ~Entity(){};
};

} // namespace NSResources

namespace std  {
    template <>
    struct hash<NSResources::Entity> {
        std::size_t operator()(NSResources::Entity const& k) const;
    };
} // namespace std