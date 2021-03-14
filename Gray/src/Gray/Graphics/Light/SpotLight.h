#pragma once

#include "LightColor.h"
#include "Platform/Opengl/Shader.h"

namespace Gray
{
	struct SpotLight
	{
		static const uint MAX_LIMIT;

		SpotLight();

		void SetUniformsFor(const Shader& shader, uint index) const;

		LightColor color;
		glm::vec3 pos;
		glm::vec3 dir;
		glm::vec3 attenuation;

		float inneCutOff;
		float outerCutOff;

	};	
}