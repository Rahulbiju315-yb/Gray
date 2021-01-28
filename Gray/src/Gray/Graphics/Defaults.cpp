#include "grpch.h"
#include "Defaults.h"
#include "Platform/Opengl/Texture.h"
#include "Gray/Image/Image.h"

namespace Gray
{
	const glm::vec3 Defaults::DEFAULT_LIGHT_DIFFUSE = glm::vec3(0.5f);
	const glm::vec3 Defaults::DEFAULT_LIGHT_AMBIENT = glm::vec3(0.0f);
	const glm::vec3 Defaults::DEFAULT_LIGHT_SPECULAR = glm::vec3(0.2f);

	const float Defaults::DEFAULT_K0 = 1.0f;
	const float Defaults::DEFAULT_K1 = 0.7f;
	const float Defaults::DEFAULT_K2 = 0.14f;

	const glm::vec3 Defaults::ORIGIN = glm::vec3(0.0f);
	const glm::vec3 Defaults::COLOR_WHITE = glm::vec3(1.0f);
	const glm::vec3 Defaults::COLOR_BLACK = glm::vec3(0.0f);

	const Texture* Defaults::BlankTex(glm::vec3 color)
	{
		static NoCopy<Texture> blank;
		if(blank->GetID())
			blank->LoadEmptyTexture(1, 1);
		return blank.Get();
	}
}