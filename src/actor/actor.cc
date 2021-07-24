#include "debug/debug.h"

#include "actor.h"
#include "geometry/geometry_base.h"

#include <iostream>
#include <string>

using namespace NSActor;

actor::actor(actor&& otherActor) noexcept
    : NSResources::Entity{std::move(otherActor)}
    , NSComponent::component_base{std::move(otherActor)}
    , NSProperty::IMoveable{std::move(otherActor)}
    , NSProperty::IScalable{std::move(otherActor)}

    , components{std::move(otherActor.components)}
    , properties{std::move(otherActor.properties)} {

    // set new parent to components
    for (auto&& x : components)
        x.second.first->SetParent(this);
}

NSComponent::component_base * actor::GetComponent(std::string const& comp_name) const noexcept {
    auto&& it = components.find(comp_name);
    if (it != components.end()) {
        return it->second.first;
    }

    return nullptr;
}

NSComponent::component_base * actor::DetachComponent(std::string const& comp_name) noexcept {
    auto && it = components.find(comp_name);
    if (it != components.end()) {
        NSComponent::component_base * oldComp = it->second.first;
        remove_properties_from_generated_arrays(it->second.second);
        components.erase(it);

        oldComp->SetParent(nullptr);
        return oldComp;
    }

    return nullptr;
}

actor & actor::DeleteComponent(std::string const& comp_name) noexcept {
    auto && it = components.find(comp_name);
    if (it != components.end()) {
        NSComponent::component_base * oldComp = it->second.first;
        remove_properties_from_generated_arrays(it->second.second);
        components.erase(it);

        delete oldComp;
    }

    return *this;
}

void actor::remove_properties_from_generated_arrays(std::vector<std::list<NSProperty::IProcessable *>::iterator> const & prop_array) noexcept {
    for (auto && property : prop_array) {
        removeProperty<NSProperty::IDrawable>(property);
        removeProperty<NSProperty::ICompound>(property);
    }
}

actor::~actor() {
    for (auto && x : components)
        delete x.second.first;
}

void actor::Process(NSGeometry::Transformation const & tr) {
    NSGeometry::Transformation const newTr{ tr + NSGeometry::Transformation{GetPosition(), GetRotation(), GetScale()} };

    processProperty<NSProperty::IDrawable>(&NSProperty::IDrawable::Draw,    newTr);
    processProperty<NSProperty::ICompound>(&NSProperty::ICompound::Process, newTr);
}

// TODO create funciton for std::type_index(typeid(NSProperty::IDrawable))
bool actor::IsDrawable() const noexcept {
    return properties.find(std::type_index(typeid(NSProperty::IDrawable))) != properties.end();
}
actor::ProcessablesList::const_iterator actor::drawable_begin() const {
    if (!IsDrawable()) gERROR("Before iteration you should check for drawable!");
    return properties.at(std::type_index(typeid(NSProperty::IDrawable))).begin();
}
actor::ProcessablesList::const_iterator actor::drawable_end() const {
    if (!IsDrawable()) gERROR("Before iteration you should check for drawable!");
    return properties.at(std::type_index(typeid(NSProperty::IDrawable))).end();
}
actor::ProcessablesList::iterator actor::drawable_begin() {
    if (!IsDrawable()) gERROR("Before iteration you should check for drawable!");
    return properties.at(std::type_index(typeid(NSProperty::IDrawable))).begin();
}
actor::ProcessablesList::iterator actor::drawable_end() {
    if (!IsDrawable()) gERROR("Before iteration you should check for drawable!");
    return properties.at(std::type_index(typeid(NSProperty::IDrawable))).end();
}
