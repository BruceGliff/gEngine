#include "debug/debug.h"

#include "actor.h"
#include "geometry/geometry_base.h"

#include <iostream>
#include <string>

using namespace Actor;

actor::actor(actor&& otherActor) noexcept
    : Resources::Entity{std::move(otherActor)}
    , Component::component_base{std::move(otherActor)}
    , Property::IMoveable{std::move(otherActor)}
    , Property::IScalable{std::move(otherActor)}

    , components{std::move(otherActor.components)}
    , properties{std::move(otherActor.properties)} {

    // set new parent to components
    for (auto&& x : components) {
        x.second.first->SetParent(this);
    }
}

Component::component_base * actor::GetComponent(std::string const& comp_name) const noexcept {
    auto&& it = components.find(comp_name);
    if (it != components.end()) {
        return it->second.first;
    }

    return nullptr;
}

Component::component_base * actor::DetachComponent(std::string const& comp_name) noexcept {
    auto && it = components.find(comp_name);
    if (it != components.end()) {
        Component::component_base * oldComp = it->second.first;
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
        Component::component_base * oldComp = it->second.first;
        remove_properties_from_generated_arrays(it->second.second);
        components.erase(it);

        delete oldComp;
    }

    return *this;
}

void actor::remove_properties_from_generated_arrays(std::vector<std::list<Property::IProcessable *>::iterator> const & prop_array) noexcept {
    for (auto && property : prop_array) {
        removeProperty<Property::IDrawable>(property);
        removeProperty<Property::ICompound>(property);
    }
}

actor::~actor() {
    for (auto && x : components) {
        delete x.second.first;
    }
}

void actor::Process(Geometry::Transformation const & tr) {
    Geometry::Transformation const newTr{ tr + Geometry::Transformation{GetPosition(), GetRotation(), GetScale()} };

    processProperty<Property::IDrawable>(&Property::IDrawable::Draw,    newTr);
    processProperty<Property::ICompound>(&Property::ICompound::Process, newTr);
}