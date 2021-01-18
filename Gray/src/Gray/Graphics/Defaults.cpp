#include "grpch.h"
#include "Defaults.h"
#include "Platform/Opengl/Texture.h"

namespace Gray
{
	const glm::vec3 Defaults::DEFAULT_LIGHT_DIFFUSE = glm::vec3(0.5f);
	const glm::vec3 Defaults::DEFAULT_LIGHT_AMBIENT = glm::vec3(0.0f);
	const glm::vec3 Defaults::DEFAULT_LIGHT_SPECULAR = glm::vec3(1.0f);

	const float Defaults::DEFAULT_K0 = 1.0f;
	const float Defaults::DEFAULT_K1 = 0.0f;
	const float Defaults::DEFAULT_K2 = 0.0f;

	const glm::vec3 Defaults::ORIGIN = glm::vec3(0.0f);
	const glm::vec3 Defaults::COLOR_WHITE = glm::vec3(1.0f);
	const glm::vec3 Defaults::COLOR_BLACK = glm::vec3(0.0f);

	const Texture* Defaults::BlankTex(glm::vec3 color)
	{
		static NoCopy<Texture> blankTexture;
		if (blankTexture->GetID() == 0)
		{

			int r = (int)(color.r);
			int g = (int)(color.g);
			int b = (int)(color.b);
			
			char data[4] = {(char)r, (char)g, (char)b, 0};

			blankTexture->LoadTextureFrom(data, 1, 1, GL_RGB, GL_RGBA);
		}
		return blankTexture.Get();
	}
}