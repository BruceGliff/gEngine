#include "Entity.h"


Resources::Entity::Entity() noexcept
{
    static int counter = 0;
    id = counter++;
}
Resources::Entity::Entity(Entity const& entity) noexcept
{
    id = entity.id;
}
Resources::Entity::Entity(Entity && entity) noexcept
{
    *this = std::move(entity);
}
void Resources::Entity::swap(Entity & entity) noexcept
{
    std::swap(id, entity.id);
}
bool Resources::Entity::operator==(Entity const& other) const noexcept
{
    return other.id == id;
}
Resources::Entity & Resources::Entity::operator=(Entity && entity) noexcept
{
    swap(entity);
    return *this;
}

int const & Resources::Entity::GetEntityID() const noexcept
{
    return id;
}

Resources::Entity & Resources::Entity::operator()() noexcept
{
    return *this;
}
Resources::Entity const & Resources::Entity::operator()() const noexcept
{
    return *this;
}
Resources::Entity & Resources::Entity::GetEntity() noexcept
{
    return *this;
}
Resources::Entity const & Resources::Entity::GetEntity() const noexcept
{
    return *this;
}


std::size_t std::hash<Resources::Entity>::operator()(Resources::Entity const& k) const
{
    return (hash<int>()(k.GetEntityID()));
}