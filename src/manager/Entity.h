#pragma once

#include <functional>

namespace Resources 
{
    // entity is mostly all objects
    // componetnts, actors, and so on
    // It is used to navigate in scene, as all objects will be mapped <entity, object>
    class Entity
    {
        int id = 0;

    public:
        Entity() noexcept;
        Entity(Entity const& entity) noexcept;
        Entity(Entity&&)                    = delete;
        Entity& operator =(Entity const&)   = delete;
        Entity& operator =(Entity&&)        = delete;

        bool operator==(Entity const& other) const noexcept;

        int & GetEntityID() noexcept;
        int const & GetEntityID() const noexcept;

        // Return entity obj
        // To be possible do: map.find(actor());
        Entity & operator()() noexcept;
        Entity const & operator()() const noexcept;

        Entity & GetEntity() noexcept;
        Entity const & GetEntity() const noexcept;
    };
}
namespace std {

    template <>
    struct hash<Resources::Entity>
    {
        std::size_t operator()(Resources::Entity const& k) const;
    };
}