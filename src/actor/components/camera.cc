#include "camera.h"
#include "geometry/geometry_base.h"
#include "process/global.h"
#include "window/window_base.h"

Component::camera::camera() : 
        fov{ 45.f }, 
        front{ 0.f, 0.f, -1.f }, 
        up{ 0.f, 1.f, 0.f }
{
}

Component::camera::camera(float fov_angle, glm::vec3 const& front_dir, glm::vec3 const& up_dir) :
        fov{fov_angle},
        front{front_dir},
        up{up_dir}
{
}

glm::vec3& Component::camera::GetFront() noexcept
{
    return front;
}

glm::vec3 const& Component::camera::GetFront() const noexcept
{
    return front;
}

glm::vec3& Component::camera::GetUp() noexcept
{
    return up;
}

glm::vec3 const& Component::camera::GetUp() const noexcept
{
    return up;
}

float& Component::camera::GetFOV() noexcept
{
    return fov;
}

float const& Component::camera::GetFOV() const noexcept
{
    return fov;
}

glm::mat4 Component::camera::GetViewMatrix() const
{
    // TODO investigate if rotation is necessaty here 
    Property::ICompound * parent = GetParent();
    Geometry::Transformation transform;
    transform.displace += GetPosition();
    //transform.rotate   += GetRotation();

    // Go up on hierarchy to got absolute transformation 
    while (parent)
    {
        if(Property::IPlaceable * ptr = dynamic_cast<Property::IPlaceable *>(parent))
        {
            transform.displace += ptr->GetPosition();
        }
        // if(Property::IRotatable * ptr = dynamic_cast<Property::IRotatable *>(parent))
        // {
        //     transform.rotate += ptr->GetRotation();
        // }

        // Parent has "parent_" only if it is component by itself!
        if(Component::component_base * ptr = dynamic_cast<Component::component_base *>(parent))
            parent = ptr->GetParent();
        else
            parent = nullptr;
    }

    // view{ glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp) };
    return glm::lookAt(transform.displace, front + transform.displace, up);
}

glm::mat4 Component::camera::GetProjectionMatrix() const
{
    Resources::WindowSizeProperty const & size = GLOBAL::GetWindow().GetWindowSize();

    return glm::perspective(glm::radians(fov), ((float) size.width) / size.height, nearClamp, farClamp);
}