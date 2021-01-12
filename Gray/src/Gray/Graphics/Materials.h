#pragma once
#include "glm/glm.hpp"
#include "Defaults.h"
#include "Platform/Opengl/Texture.h"
namespace Gray
{
	class Material
	{
	public:
		Material()
			: shininess(32.0f), diffuse(nullptr), specular(nullptr), emission(nullptr), ID(0)
		{
		}

		bool operator==(const Material& other) 
		{
			return (diffuse == other.diffuse)
				&& (specular == other.specular)
				&& (emission == other.emission)
				&& (shininess == other.shininess);
		}

		void SetDiffuse(Texture* diff) { diffuse = diff; }
		void SetSpecular(Texture* spec) { specular = spec; }
		void SetEmission(Texture* emm) { emission = emm; }
		void SetShininess(float sh) { shininess = sh; }

		Texture* GetDiffuse() const { return diffuse; }
		Texture* GetSpecular() const { return specular; }
		Texture* GetEmission() const { return emission; }

		float GetShininess() const { return shininess; }

		uint ID;
	private:
		Texture* diffuse;
		Texture* specular;
		Texture* emission;

		float shininess;
	};

}