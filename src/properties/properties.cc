#include "properties.h"

Property::IPlaceable::IPlaceable() : anchor_position{ 0.f, 0.f, 0.f }
{}

Property::IPlaceable::IPlaceable(glm::vec3 const& pos) : anchor_position{pos}
{}

glm::vec3& Property::IPlaceable::GetPosition() noexcept
{
	return anchor_position;
}

glm::vec3 const& Property::IPlaceable::GetPosition() const noexcept
{
	return anchor_position;
}


Property::IMoveable & Property::IMoveable::SetPosition(glm::vec3 const& pos) noexcept
{
	anchor_position = pos;

	return *this;
}

glm::vec3& Property::IRotatable::GetRotation() noexcept
{
	return rotator;
}
glm::vec3 const& Property::IRotatable::GetRotation() const noexcept
{
	return rotator;
}

glm::vec3& Property::IScalable::GetScale() noexcept
{
	return scale;
}
glm::vec3 const& Property::IScalable::GetScale() const noexcept
{
	return scale;
}
