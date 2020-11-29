#pragma once

#include "glm/glm.hpp"
#include "Platform/Opengl/Texture.h"
namespace Gray
{
	class Defaults
	{
	public:
		static const Texture DEFAULT_EMISSION;
		static const Texture DEFAULT_DIFFUSE;
		static const Texture DEFAULT_SPECULAR;
		static const float DEFAULT_SHININESS;

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