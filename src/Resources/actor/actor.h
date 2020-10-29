#pragma once

#include <glm/vec3.hpp>

namespace Actor
{

	// TODO remove final
	// class that represent behavior of playable object
	// now it is just camera
	// TODO separate behavior to movement component, camera component and ...
	class actor_base final
	{
		// TODO Encapsulate this!
	public:
		// This params for anchor
		glm::vec3 cameraPos		{ 0.0f, 0.0f, 3.0f };
		glm::vec3 cameraFront	{ 0.0f, 0.0f, -1.0f };
		glm::vec3 cameraUp		{ 0.0f, 1.0f, 0.0f };

		// This params for camera
		float fov = 45.f;
	};




}