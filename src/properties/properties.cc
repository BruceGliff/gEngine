#include "properties.h"

Property::IPlaceable::IPlaceable() : anchor_position{ 0.f, 0.f, 3.f }
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
}
