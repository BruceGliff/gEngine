#include "debug/debug.h"

template<typename T, typename ... Args>
T * Scene::Scene::Spawn(Args && ... args)
{
    // We assume that type has to be actor to be spawned in scene!
    if (!std::is_base_of<Actor::actor, T>::value)
    {
        gWARNING(std::string{"Type is not an actor: "} + typeid(T).name());
        return nullptr;
    }

    T * p = new T{std::forward<Args>(args) ...};
    Actor::actor * pA = dynamic_cast<Actor::actor *>(p);

    if (!pA) {
        gWARNING(std::string{"This is not suppose to happen: Check with is_base_of<> gave wrong result!\n "} + typeid(T).name());
        return nullptr;
    }

    //scene[pA->GetEntity()] = pA;
    scene.emplace(pA->GetEntity(), pA);

    return p;
    }

template<typename T, typename NoRefT>
NoRefT * Scene::Scene:: Attach(T && obj)
{
    // We assume that type has to be actor to be spawned in scene!
    if (typeid(Actor::actor *) != typeid(NoRefT *))
    {
        gWARNING(std::string{"Type is not an actor: "} + typeid(T).name());
        return nullptr;
    }

    NoRefT * p = new NoRefT{std::move(obj)};
    Actor::actor * pA = dynamic_cast<Actor::actor *>(p); // This should always appear as check has been completed

    if (!pA) {
        gWARNING(std::string{"This is not suppose to happen: Check with typeid() gave wrong result! State of obj has been corrupt!\n "} + typeid(T).name());
        return nullptr;
    }

    auto && it = scene.find(pA->GetEntity());
    if (it != scene.end())
    {
        gWARNING(std::string{"This is not suppose to happen: Object already in scene. id: "} + std::to_string(pA->GetEntityID()));
        return nullptr;
    }
    
    scene.emplace(pA->GetEntity(), pA);

    return p;
}

template <typename T>
T * Scene::Scene::GetActor(Resources::Entity const & en) const noexcept
{
    auto && it = scene.find(en);
    if (it == scene.end())
    {
        gWARNING(std::string{"Attempt to get unexisted actor id: "} + std::to_string(en.GetEntityID()));
        return nullptr;
    }

    return dynamic_cast<T *>(it->second.get());
}