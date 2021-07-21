#include "Entity.h"

using namespace NSResources;

Entity::Entity() noexcept {
    static int counter = 0;
    id = counter++;
}
Entity::Entity(Entity const& entity) noexcept {
    id = entity.id;
}
Entity::Entity(Entity && entity) noexcept {
    *this = std::move(entity);
}
void Entity::swap(Entity & entity) noexcept {
    std::swap(id, entity.id);
}
bool Entity::operator==(Entity const& other) const noexcept {
    return other.id == id;
}
Entity & Entity::operator=(Entity && entity) noexcept {
    swap(entity);
    return *this;
}
int const & Entity::GetEntityID() const noexcept {
    return id;
}
Entity & Entity::operator()() noexcept {
    return *this;
}
Entity const & Entity::operator()() const noexcept {
    return *this;
}
Entity & Entity::GetEntity() noexcept {
    return *this;
}
Entity const & Entity::GetEntity() const noexcept {
    return *this;
}

std::size_t std::hash<Entity>::operator()(Entity const& k) const
{
    return (hash<int>()(k.GetEntityID()));
}