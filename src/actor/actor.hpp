#include "debug/debug.h"

#include <functional>

template <typename T, typename ... Args>
Actor::actor & Actor::actor::AttachComponent(std::string const & comp_name, Args && ... args) {
    if (!std::is_base_of<Component::component_base, T>::value) {
        gWARNING(std::string{"Attaching not component: "} + typeid(T).name());
        return *this;
    }
    
    // first - make pair
    // second - replace it

    T * p = new T{std::forward<Args>(args) ...};
    Component::component_base * component = p;

    // set this class as parent for component
    component->SetParent(this);

    // Aggregation is a pair of component and array of properties of the component
    ComponentAggregation aggregation;
    aggregation.first = component;


    insertProperty<Property::IDrawable>(component, /*OUT*/ aggregation);
    insertProperty<Property::ICompound>(component, /*OUT*/ aggregation);


    auto&& it = components.find(comp_name);
    if (it != components.end()) {
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

template<typename PropertyToInsert>
void Actor::actor::insertProperty(Component::component_base * component, ComponentAggregation & aggregation) {
    if (PropertyToInsert * p = dynamic_cast<PropertyToInsert *>(component)) {
        properties[std::type_index(typeid(PropertyToInsert))].push_front(p);
        aggregation.second.push_back(properties[std::type_index(typeid(PropertyToInsert))].begin());
    }
}
template<typename PropertyToDelete>
void Actor::actor::removeProperty(std::list<Property::IProcessable *>::iterator const & property) {
    // TODO check if this check is required
    auto && prop = properties.find(std::type_index(typeid(PropertyToDelete)));

    if (prop != properties.end()) {
        prop->second.remove(*property);
    }
}

template <typename componentType>
componentType * Actor::actor::GetComponentByName(std::string const& comp_name) const noexcept {
    auto&& it = components.find(comp_name);
    if (it != components.end()) {
        return static_cast<componentType *>(it->second.first);
    }

    return nullptr;
}

template<typename T, typename Function, typename ... Args>
void Actor::actor::processProperty(Function && call, Args && ... args) {
    for (auto && x : properties[std::type_index(typeid(T))]) {
        T * pProp = static_cast<T *>(x);

        auto process = std::bind( call, pProp, std::forward<Args>(args)... );
        process();
    }
}