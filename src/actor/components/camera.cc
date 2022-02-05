#include "camera.h"
#include "../../geometry/geometry_base.h"
#include "../../process/global.h"
#include "../../window/window_base.h"

using namespace NSComponent;

camera::camera()
    : fov{ 45.f }
    , front{ 0.f, 0.f, -1.f }
    , up{ 0.f, 1.f, 0.f } {
}

camera::camera(float fov_angle, glm::vec3 const& front_dir, glm::vec3 const& up_dir)
    : fov{fov_angle}
    , front{front_dir}
    , up{up_dir} {
}

glm::vec3& camera::GetFront() noexcept {
    return front;
}

glm::vec3 const& camera::GetFront() const noexcept {
    return front;
}

glm::vec3& camera::GetUp() noexcept {
    return up;
}

glm::vec3 const& camera::GetUp() const noexcept {
    return up;
}

float& camera::GetFOV() noexcept {
    return fov;
}

float const& camera::GetFOV() const noexcept {
    return fov;
}

// TODO separate global position
glm::mat4 camera::GetViewMatrix() const {
    // TODO investigate if rotation is necessaty here
    NSProperty::ICompound * parent = GetParent();
    NSGeometry::Transformation transform;
    transform.displace += GetPosition();
    //transform.rotate   += GetRotation();

    // Go up on hierarchy to get absolute transformation
    while (parent) {
        if(NSProperty::IPlaceable * ptr = dynamic_cast<NSProperty::IPlaceable *>(parent)) {
            transform.displace += ptr->GetPosition();
        }
        // if(Property::IRotatable * ptr = dynamic_cast<Property::IRotatable *>(parent)) {
        //     transform.rotate += ptr->GetRotation();
        // }

        // Parent has "parent_" only if it is component by itself!
        if(NSComponent::component_base * ptr = dynamic_cast<NSComponent::component_base *>(parent)) {
            parent = ptr->GetParent();
        } else {
            parent = nullptr;
        }
    }

    // view{ glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp) };
    return glm::lookAt(transform.displace, front + transform.displace, up);
}

glm::mat4 NSComponent::camera::GetProjectionMatrix() const {
    NSResources::WindowSizeProperty const & size = GLOBAL::GetWindow().GetWindowSize();

    return glm::perspective(glm::radians(fov), ((float) size.width) / size.height, nearClamp, farClamp);
}
