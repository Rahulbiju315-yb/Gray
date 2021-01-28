#pragma once

#include "LightColor.h"
#include "Platform/Opengl/Shader.h"

namespace Gray
{
	
	struct DirectionalLight
	{
		static const uint MAX_LIMIT;

		DirectionalLight();
		void SetUniformsFor(const Shader& shader, uint index);

		LightColor color;
		glm::vec3 dir;
	};
}