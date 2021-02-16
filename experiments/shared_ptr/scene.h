#pragma once
#include <memory>
#include <unordered_map>
#include "entity.h"
#include "actor.h"

class Scene final
{
    std::unordered_map<Entity, std::shared_ptr<actor>> scene;
    // TODO make light seperate


    typedef std::unordered_map<Entity, std::shared_ptr<actor>>::iterator iterator;
    typedef std::unordered_map<Entity, std::shared_ptr<actor>>::const_iterator const_iterator;

public:
    Scene() = default;
    Scene(Scene const&)				= delete;
    Scene(Scene&&)					= delete;
    Scene& operator= (Scene const&) = delete;
    Scene& operator= (Scene&&)		= delete;

    // Spawn an object at scene
    template<typename T, typename ... Args>
    std::shared_ptr<actor> Spawn(Args && ... args)
    {
        std::shared_ptr<T> p = std::make_shared<T>(std::forward<Args>(args) ...);
        std::shared_ptr<actor> pA = std::dynamic_pointer_cast<actor>(p);
        if (pA.get() == nullptr)
        {
            std::cout << "Type is not an actor" << std::endl;
            return nullptr;
        }

        return scene[pA->GetEntity()] = std::move(pA);
    }

    iterator begin()
    {
        return scene.begin();
    }
    iterator end()
    {
        return scene.end();
    }
    const_iterator begin() const
    {
        return scene.begin();
    }
    const_iterator end() const
    {
        return scene.end();
    }

    // Attach already created object to scene
    // Resource occupation comes to scene
    // If somehow object is already in scene, then do nothing
    template<typename T, typename NoRefT = typename std::remove_reference<T>::type>
    std::shared_ptr<NoRefT> Attach(T && obj)
    {
        std::shared_ptr<NoRefT> p = std::make_shared<NoRefT>( std::move(obj) );
        std::shared_ptr<actor> pA = std::dynamic_pointer_cast<actor>(p);
        if (pA.get() == nullptr)
        {
            std::cout << "Type is not an actor" << std::endl;
            return nullptr;
        }

        auto && it = scene.find(pA->GetEntity());
        if (it != scene.end())
        {
            std::cout << "This is not suppose to happen" << std::endl;
            return nullptr;
        }
        
        // scene[pA->GetEntity] does copy of entity
        scene[pA->GetEntity()] = std::move(pA);

        return p;
    }

    std::shared_ptr<actor> GetActor(Entity const & en) const noexcept
    {
        auto && it = scene.find(en);
        if (it == scene.end())
        {
            std::cout << "Attemp to get unexisted actor" << std::endl;;
            return nullptr;
        }

        return it->second;
    }
    // Return shared_ptr of type T with given Entity(id) or nullptr if it is not found or it cannot be type T
    template <typename T>
    std::shared_ptr<T> GetActor(Entity const & en) const noexcept
    {
        auto && it = scene.find(en);
        if (it == scene.end())
        {
            std::cout << "Attempt to get null " << std::endl;
            return nullptr;
        }

        std::shared_ptr<T> pA = std::dynamic_pointer_cast<T>(it->second);
        return pA;
    }

    std::shared_ptr<actor> operator[](Entity const & en) const noexcept
    {
        return GetActor(en);
    }


};