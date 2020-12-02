#include "grpch.h"
#include "Defaults.h"
#include "Platform/Opengl/Texture.h"

namespace Gray
{
	const Texture Defaults::DEFAULT_EMISSION = Texture();
	const Texture Defaults::DEFAULT_SPECULAR = Texture();
	const Texture Defaults::DEFAULT_DIFFUSE = Texture();
	const float Defaults::DEFAULT_SHININESS = 32.0f;

	const glm::vec3 Defaults::DEFAULT_LIGHT_DIFFUSE = glm::vec3(0.5f);
	const glm::vec3 Defaults::DEFAULT_LIGHT_AMBIENT = glm::vec3(0.1f);
	const glm::vec3 Defaults::DEFAULT_LIGHT_SPECULAR = glm::vec3(1.0f);

	const float Defaults::DEFAULT_K0 = 1.0f;
	const float Defaults::DEFAULT_K1 = 0.14f;
	const float Defaults::DEFAULT_K2 = 0.07f;

	const glm::vec3 Defaults::ORIGIN = glm::vec3(0.0f);
	const glm::vec3 Defaults::COLOR_WHITE = glm::vec3(1.0f);
	const glm::vec3 Defaults::COLOR_BLACK = glm::vec3(0.0f);
	
}