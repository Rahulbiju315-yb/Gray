#pragma once

#include "glm/glm.hpp"

namespace Gray
{
	class Source
	{
	public:
		virtual const glm::vec3& GetPos() = 0;
		virtual const glm::vec3& GetDir() = 0;
	};

}