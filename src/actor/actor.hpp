#include "debug/debug.h"

template <typename T, typename ... Args>
Actor::actor & Actor::actor::AttachComponent(std::string const & comp_name, Args && ... args)
{
    if (!std::is_base_of<Component::component_base, T>::value) {
        gWARNING(std::string{"Attaching not component: "} + typeid(T).name());
        return *this;
    }
    
    // to get hints when insert propertied into define;
    using namespace Property;
    // first - make pair
    // second - replace it

    T * p = new T{std::forward<Args>(args) ...};
    Component::component_base * component = p;

    // set this class as parent for component
    component->SetParent(this);

    // Aggregation is a pair of component and array of properties of the component
    ComponentAggregation aggregation;
    aggregation.first = component;

    INSERT_PROPERTY(IDrawable);
    INSERT_PROPERTY(ICompound);


    auto&& it = components.find(comp_name);
    if (it != components.end())
    {
        // delete old components
        // TODO this is work part(maybe)
        // ComponentAggregation oldAggr = std::move(it->second);
        // Component::component_base * oldComp = it->second.first;
        // it->second = std::move(aggregation);
        // remove_properties_from_generated_arrays(oldAggr.second);

        std::swap(aggregation, it->second);
        delete aggregation.first;

        return *this;
    }

    components[comp_name] = std::move(aggregation);
    return *this;

}

template <typename componentType>
componentType * Actor::actor::GetComponentByName(std::string const& comp_name) const noexcept
{
    auto&& it = components.find(comp_name);
    if (it != components.end())
    {
        // TODO may be dynamic_cast<>?
        return static_cast<componentType *>(it->second.first);
    }

    return nullptr;
}