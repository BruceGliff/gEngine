#pragma once    
#include <functional>
#include <iostream>

class Entity
{
    int id = -1;

public:
    Entity() noexcept;
    Entity(Entity const& entity) noexcept;
    Entity(Entity&& e) noexcept
    {
        *this = std::move(e);

        std::cout << "Move En " << id << std::endl;
    }
    Entity& operator =(Entity const&)   = delete;
    Entity& operator =(Entity&& en)
    {
        swap(en);
        return *this;
    }
    // Swap id from different entities
    void swap(Entity & en) noexcept
    {
        std::swap(en.id, id);
    }

    bool operator==(Entity const& other) const noexcept;

    int const & GetEntityID() const noexcept;

    void dump() const
    {
        std::cout << id << std::endl;
    }
    // Return entity obj
    // To be possible do: map.find(actor());
    Entity & operator()() noexcept;
    Entity const & operator()() const noexcept;

    Entity & GetEntity() noexcept;
    Entity const & GetEntity() const noexcept;

    virtual ~Entity() {}
};

namespace std 
{
    template <>
    struct hash<Entity>
    {
        std::size_t operator()(Entity const& k) const;
    };
}

Entity::Entity() noexcept
{
    static int counter = 0;
    id = counter++;
    std::cout << "const En " << id << std::endl;
}
Entity::Entity(Entity const& entity) noexcept
{
    id = entity.id;
    std::cout << "Copy En " << id << std::endl;
}

bool Entity::operator==(Entity const& other) const noexcept
{
    return other.id == id;
}

int const & Entity::GetEntityID() const noexcept
{
    return id;
}

Entity & Entity::operator()() noexcept
{
    return *this;
}
Entity const & Entity::operator()() const noexcept
{
    return *this;
}
Entity & Entity::GetEntity() noexcept
{
    return *this;
}
Entity const & Entity::GetEntity() const noexcept
{
    return *this;
}


std::size_t std::hash<Entity>::operator()(Entity const& k) const
{
    return (hash<int>()(k.GetEntityID()));
}