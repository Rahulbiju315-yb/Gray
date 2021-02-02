#pragma once

#include "glm/glm.hpp"
namespace Gray
{
	struct Perspective
	{
		float fov; // field of view
		float aspectRatio;
		float zLimNear;
		float zLimFar;

		void GetProjectionMatrix(glm::mat4& proj);
	};
	static Perspective defaultPersepective{ glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f };
}