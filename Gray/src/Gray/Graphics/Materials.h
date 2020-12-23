#pragma once
#include "glm/glm.hpp"
#include "Defaults.h"
#include "Platform/Opengl/Texture.h"
namespace Gray
{

	//move code to .cpp file
	struct Material
	{
	public:
		Material() : shininess(32)
		{


		}

		const std::vector<Texture>& GetEmissionMaps() const { return emissionMaps; }
		const std::vector<Texture>& GetDiffuseMaps() const { return diffuseMaps; }
		const std::vector<Texture>& GetSpecularMaps() const { return specularMaps; }
		const float GetShininess() const { return shininess; }

		void AddEmission(Texture emission) { emissionMaps.push_back(emission); }
		void AddDiffuse(Texture diffuse) { diffuseMaps.push_back(diffuse);  }
		void AddSpecular(Texture specular) { specularMaps.push_back(specular); }
		void SetShininess(float shininess) { this->shininess = shininess; }

	private:
		std::vector<Texture> emissionMaps;
		std::vector<Texture> specularMaps;
		std::vector<Texture> diffuseMaps;

		float shininess;
	};
}