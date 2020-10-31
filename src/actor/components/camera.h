#pragma once

#include "component_base.h"

#include <glm/vec3.hpp>

namespace Component
{
	class camera : public component_base
	{
		float fov;
		glm::vec3 front;
		glm::vec3 up;
		// TODO move ot constructor
		glm::vec3 hand_dir{ 0.f, 0.f, -3.f };
		float hand_lenght = 0.f;

	public:
		camera();
		camera(float fov_angle, glm::vec3 const& front, glm::vec3 const & up);
		camera(camera const&)				= delete;
		camera(camera&&)					= delete;
		camera& operator= (camera const&)	= delete;
		camera& operator= (camera&&)		= delete;

		glm::vec3& GetFront() noexcept;
		glm::vec3 const & GetFront() const noexcept;

		glm::vec3& GetUp() noexcept;
		glm::vec3 const& GetUp() const noexcept;

		float& GetFOV() noexcept;
		float const& GetFOV() const noexcept;

		virtual ~camera() {};
	};
}