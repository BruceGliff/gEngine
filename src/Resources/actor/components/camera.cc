#include "camera.h"

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
