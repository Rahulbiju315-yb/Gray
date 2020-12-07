#pragma once

#include "glm/glm.hpp"
#include "Gray/Graphics/Defaults.h"

namespace Gray
{
	struct LightColor
	{
	public:

		LightColor(glm::vec3 ambient = Defaults::DEFAULT_LIGHT_AMBIENT,
			glm::vec3 diffuse = Defaults::DEFAULT_LIGHT_DIFFUSE,
			glm::vec3 specular = Defaults::DEFAULT_LIGHT_SPECULAR)
		{
			this->ambient = ambient;
			this->diffuse = diffuse;
			this->specular = specular;
		};

		const glm::vec3& GetAmbient() { return ambient; }
		const glm::vec3& GetDiffuse() { return diffuse; }
		const glm::vec3& GetSpecular() { return specular; }

		void SetAmbient(glm::vec3 ambient) { this->ambient = ambient; }
		void SetDiffuse(glm::vec3 diffuse) { this->diffuse = diffuse; }
		void SetSpecular(glm::vec3 specular) { this->specular = specular; }

	private:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}