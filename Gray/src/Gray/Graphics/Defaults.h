#pragma once

#include "glm/glm.hpp"

#include "Platform/Opengl/Texture.h"
#include "Platform/Opengl/VertexBuffer.h"

namespace Gray
{
	class Defaults
	{
	public:
		
		static const Texture* BlankTex(glm::vec3 color=glm::vec3(0));
		static const glm::vec3 DEFAULT_LIGHT_DIFFUSE;
		static const glm::vec3 DEFAULT_LIGHT_AMBIENT;
		static const glm::vec3 DEFAULT_LIGHT_SPECULAR;

		static const float DEFAULT_K0;
		static const float DEFAULT_K1;
		static const float DEFAULT_K2;

		static const glm::vec3 ORIGIN;
		static const glm::vec3 Defaults::COLOR_WHITE;
		static const glm::vec3 Defaults::COLOR_BLACK;

	};
}