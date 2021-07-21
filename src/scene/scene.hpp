#include "debug/debug.h"

template<typename T, typename ... Args>
T * NSScene::Scene::Spawn(Args && ... args) {
    // We assume that type has to be actor to be spawned in scene!
    if (!std::is_base_of<NSActor::actor, T>::value) {
        gWARNING(std::string{"Type is not an actor: "} + typeid(T).name());
        return nullptr;
    }

    T * p = new T{std::forward<Args>(args) ...};
    NSActor::actor * pA = dynamic_cast<NSActor::actor *>(p);

    if (!pA) {
        gWARNING(std::string{"This is not suppose to happen: Check with is_base_of<> gave wrong result!\n "} + typeid(T).name());
        return nullptr;
    }

    auto spawned = scene.emplace(pA->GetEntity(), pA);
    blendedObjects.push_back(spawned.first);

    return p;
}

template<typename T, typename NoRefT>
NoRefT * NSScene::Scene::Attach(T && obj) {
    // We assume that type has to be actor to be spawned in scene!
    if (typeid(NSActor::actor *) != typeid(NoRefT *)) {
        gWARNING(std::string{"Type is not an actor: "} + typeid(T).name());
        return nullptr;
    }

    NoRefT * p = new NoRefT{std::move(obj)};
    NSActor::actor * pA = dynamic_cast<NSActor::actor *>(p); // This should always appear as check has been completed

    if (!pA) {
        gWARNING(std::string{"This is not suppose to happen: Check with typeid() gave wrong result! State of obj has been corrupt!\n "} + typeid(T).name());
        return nullptr;
    }

    auto && it = scene.find(pA->GetEntity());
    if (it != scene.end()) {
        gWARNING(std::string{"This is not suppose to happen: Object already in scene. id: "} + std::to_string(pA->GetEntityID()));
        return nullptr;
    }
    
    auto spawned = scene.emplace(pA->GetEntity(), pA);
    blendedObjects.push_back(spawned.first);

    return p;
}

template <typename T>
T * NSScene::Scene::GetActor(NSResources::Entity const & en) const noexcept {
    auto && it = scene.find(en);
    if (it == scene.end()) {
        gWARNING(std::string{"Attempt to get unexisted actor id: "} + std::to_string(en.GetEntityID()));
        return nullptr;
    }

    return dynamic_cast<T *>(it->second.get());
}