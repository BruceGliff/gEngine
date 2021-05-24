#pragma once

#include "components/component_base.h"
#include "properties/properties.h"
#include "manager/Entity.h"

#include <unordered_map>
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <typeindex>

namespace Renderer {
    class ShaderProgram;
}
namespace Geometry {
    class Transformation;
}

namespace Actor {
// Class represent main object in scene.
// It contains components and can be processes to draw or to calculate physics(in future)
class actor
// All class must be movable and if it has complex move object, then appears in move constructor as
// Resources::Entity{std::move(otherActor)}
    : public Resources::Entity
    , public Property::ICompound
    , public Property::IScalable
    , public Property::IMoveable
    , public Property::IRotatable
    , public Component::component_base {// component_base after ICompound

    // For easy run-time drawing all compomenents separates by their behavior and then running across only one
    // array without casts (separated by type in unordered_map).
    // Hovewer all pointers in general are the same object, only Component::component_base * represent the
    // real object what can be deleted.
    // We assume that one component may have a lot of properties, that would be represented as IProcessable *
    // All operations on component must accompanied with operations
    // insertProperty, removeProperty, processProperty

    typedef std::pair<Component::component_base*, std::vector<std::list<Property::IProcessable *>::iterator>> ComponentAggregation;
    typedef std::unordered_map<std::string, ComponentAggregation> ComponentMap;
    ComponentMap components {};

    std::unordered_map<std::type_index, std::list<Property::IProcessable *>> properties {};

    // TODO Check if remove throw an exception
    void remove_properties_from_generated_arrays(std::vector<std::list<Property::IProcessable *>::iterator> const & prop_array) noexcept;

    // insert properties are contained in component into aggregation
    template<typename PropertyToInsert>
    void insertProperty(Component::component_base * component, ComponentAggregation & /*OUT*/ aggregation);

    // revome property from arrays TODO : which array?
    template<typename PropertyToDelete>
    void removeProperty(std::list<Property::IProcessable *>::iterator const & property);

    // Process property.
    // Each property has to be processed within own function
    template<typename T, typename Function, typename ... Args>
    void processProperty(Function && process, Args && ... args);

public:
    actor() = default;
    actor(actor const&)             = delete;
    actor(actor&& otherActor) noexcept;
    actor& operator= (actor const&) = delete;
    actor& operator= (actor&&)      = delete;


    // Attach component to object by name.
    // Reattaches component if it already exists and deletes old
    // Call: AttachComponent<Component::type>(name, params for type constructor)
    template <typename T, typename ... Args>
    actor & AttachComponent(std::string const & comp_name, Args && ... args);

    // Get component by name. Return nullptr if it was not found. Did not delete from actor
    Component::component_base * GetComponent(std::string const& comp_name) const noexcept;
    // Get component by name with occured cast to necessaty component with type T
    // Return nullptr if cast is failed, or if this component did not found. Did not delete from actor
    template <typename componentType>
    componentType * GetComponentByName(std::string const& comp_name) const noexcept;

    // Get component by name. Return nullptr if it was not found. Removed from actor. Memory did not free
    Component::component_base * DetachComponent(std::string const & comp_name) noexcept;

    // Delete component by name. Do nothing if it is not found
    actor & DeleteComponent(std::string const & comp_name) noexcept;

    // Handle behavior of class. Do drawing or physics or so one
    virtual void Process(Geometry::Transformation const &) override;

    virtual ~actor();
};

} // namespace Actor

#include  "actor.hpp"
