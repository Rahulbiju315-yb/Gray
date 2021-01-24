#pragma once

#include "glm/glm.hpp"

namespace Gray
{
	struct Vertex
	{
		glm::vec3 pos; 
		glm::vec3 normal;
		glm::vec2 texCoord;
	};

	struct Face
	{
		uint v0;	uint v1;	uint v2;
	};

}