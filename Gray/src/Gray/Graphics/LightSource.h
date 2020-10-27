#pragma once

#include "glm/glm.hpp"

namespace Gray
{
	class LightSource
	{
	public:
		virtual const glm::vec4& GetColor() = 0;
		virtual void SetColor(glm::vec4 color) = 0;
		
		virtual void SetPos(glm::vec3 pos) = 0;
		virtual const glm::vec3& GetPos(glm::vec3 pos) = 0;

	};
}