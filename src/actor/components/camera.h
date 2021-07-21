#pragma once

#include "component_base.h"
#include "properties/properties.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace NSComponent {

    class camera
        : public component_base
        , public NSProperty::IMoveable
        , public NSProperty::IRotatable
{
    float fov {};
    glm::vec3 front {};
    glm::vec3 up {};

    float nearClamp {0.1f};
    float farClamp  {10000.f};

public:
    camera();
    camera(float fov_angle, glm::vec3 const & front, glm::vec3 const & up);
    camera(camera const&)               = delete;
    camera(camera&&)                    = delete;
    camera& operator= (camera const&)   = delete;
    camera& operator= (camera&&)        = delete;

    glm::vec3& GetFront() noexcept;
    glm::vec3 const & GetFront() const noexcept;

    glm::vec3& GetUp() noexcept;
    glm::vec3 const& GetUp() const noexcept;

    float& GetFOV() noexcept;
    float const& GetFOV() const noexcept;

    // Calculate view matrix depend on camera absolute transformation
    glm::mat4 GetViewMatrix() const;

    // Calculate projection matrix depend on camera fov 
    glm::mat4 GetProjectionMatrix() const;


    virtual ~camera() {};
};

} // namepace Component