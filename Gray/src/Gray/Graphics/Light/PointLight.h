#pragma once

#include "LightColor.h"
#include "Platform/Opengl/Shader.h"
namespace Gray
{
	struct PointLight
	{
		static const uint MAX_LIMIT;

		PointLight();
		void SetUniformsFor(const Shader& shader, uint index) const;

		LightColor color;
		glm::vec3 pos;
		glm::vec3 attenuation;

	};
}