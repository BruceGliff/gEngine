#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>
#include <list>

#include "entity.h"

#define PROPERTIES_ARRAY(prop)																			\
	std::list<void *> Array_##prop;	


#define INSERT_PROPERTY(prop)																			\
	if ( prop * x = dynamic_cast< prop *>(component))								\
	{																									\
		Array_##prop.push_front( reinterpret_cast<void *>(x));											\
		aggregation.second.push_back(Array_##prop.begin());												\
	}

#define REMOVE_PROPERTY(prop)																			\
	Array_##prop.remove(*property);

#define MOVE_PROPERTY(prop) \
    Array_##prop = std::move(a.Array_##prop)

class component_base
{
public:
    component_base() {std::cout << "Comp \n";}
    component_base(component_base const&)				= delete;
    component_base(component_base&&)					= delete;
    component_base& operator= (component_base const&)	= delete;
    component_base& operator= (component_base&&)		= delete;

    virtual ~component_base() {std::cout << "Comp delete " << std::endl;}
};



class IScalable
{
private:
    /* data */
public:
    IScalable(/* args */) = default;

    virtual ~IScalable() {}
};

class camera final  : public component_base, public IScalable
{
    public:
    int id = 0;
public:
    camera() { static int i = 0;
    id = i++;}
    camera(camera const&)				= delete;
    camera(camera&&)					= delete;
    camera& operator= (camera const&)	= delete;
    camera& operator= (camera&&)		= delete;


};


class actor :   public Entity,
                public IScalable
	{public:
		// For easy run-time drawing all compomenents separates by their behavior and then running across only one
		// array without casts.
		// Hovewer all pointers in general are the same object, only Component::component_base * represent the
		// physicaly object what can be deleted.
		// All operations on component must accompanied with operations on PROPERTIES_ARRAY(INSERT, REMOVE)
		typedef std::pair<component_base*, std::vector<std::list<void *>::iterator>> ComponentAggregation;
		typedef std::unordered_map<std::string, ComponentAggregation> ComponentMap;
		ComponentMap components;

        int * a_ = nullptr;

		PROPERTIES_ARRAY(IScalable);

		// TODO Check if remove throw an exception
		void remove_properties_from(std::vector<std::list<void *>::iterator> const & prop_array) noexcept
        {
            for (auto && property : prop_array)
            {
                REMOVE_PROPERTY(IScalable);
            }
        }

		

	public:
		actor() { a_ = new int[10];}
		actor(actor const& a) = delete;
		actor(actor&& a) noexcept :
            Entity{std::move(a)}
        {
            components = std::move(a.components);
            MOVE_PROPERTY(IScalable);
            std::swap(a_, a.a_);
            std::cout << "Move construct " << GetEntityID() << " from " << a.GetEntityID() << std::endl; 
        }
		actor& operator= (actor const&) = delete;
		actor& operator= (actor&& a) = delete;

		// Attach component to object by name. Class occupies given resources and releases them by himself
		// Reattaches component if it already exists and deletes old
		actor & AttachComponent(std::string const& comp_name, component_base * component)
        {
            // to get hints when insert propertied into define;
            // firstly make pair
            // secondly replace it
            ComponentAggregation aggregation;
            aggregation.first = component;

            INSERT_PROPERTY(IScalable);


            auto&& it = components.find(comp_name);
            if (it != components.end())
            {
                // // delete old components
                // ComponentAggregation oldAggr = std::move(it->second);
                // component_base * oldComp = it->second.first;
                // it->second = std::move(aggregation);
                // remove_properties_from(oldAggr.second);

                std::swap(it->second, aggregation);

                delete aggregation.first;

                return *this;
            }

            components[comp_name] = std::move(aggregation);

            return *this;
        }

		// Get component by name. Return nullptr if it was not found. Did not delete from actor
		component_base * GetComponentByName(std::string const& comp_name) const noexcept
        {
            auto&& it = components.find(comp_name);
            if (it != components.end())
            {
                return it->second.first;
            }

            return nullptr;
        }
        // Get component by name with occured cast to necessaty component with type T
        // Return nullptr if cast is failed, or if this component did not found. Did not free memory
        template <typename T>
        T * GetComponentByName(std::string const& comp_name) const noexcept
        {
            auto&& it = components.find(comp_name);
            if (it != components.end())
            {
                return dynamic_cast<T *>(it->second.first);
            }

            return nullptr;
        }

		// Get component by name. Return nullptr if it was not found. Removed from actor. Memory did not free
		component_base * DetachComponent(std::string const & comp_name) noexcept
        {
        	auto && it = components.find(comp_name);
            if (it != components.end())
            {
                component_base * oldComp = it->second.first;
                remove_properties_from(it->second.second);
                components.erase(it);

                return oldComp;
            }

            return nullptr;
        }

		// Delete component by name. Do nothing if it is not found
		actor & DeleteComponent(std::string const & comp_name) noexcept
        {
            auto && it = components.find(comp_name);
            if (it != components.end())
            {
                component_base * oldComp = it->second.first;
                remove_properties_from(it->second.second);
                components.erase(it);

                delete oldComp;
            }
        }

		// Handle behavior of class. Do drawing or physics or so one
		virtual void Process()
        {
            std::cout << "Processing " << std::endl;
        }

		virtual ~actor()
        {
            std::cout << "Actor del with id: " << GetEntityID() << std::endl;
            delete[] a_;
            for (auto && x : components)
            {
		        delete x.second.first;
                std::cout << "Not -1" << std::endl;
            }
        }
	};

    class mya : public actor
    {
    public:
        void Process() override
        {std::cout << "MYA\n";}
    };
    