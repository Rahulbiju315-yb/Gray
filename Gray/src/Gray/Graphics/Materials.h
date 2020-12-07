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
		Material(Texture emission = Defaults::DEFAULT_EMISSION,
			Texture diffuse = Defaults::DEFAULT_DIFFUSE,
			Texture specular = Defaults::DEFAULT_SPECULAR,
			float shininess = Defaults::DEFAULT_SHININESS)

		{
			this->emission = emission;
			this->diffuse = diffuse;
			this->specular = specular;
			this->shininess = shininess;
		}

		const Texture* GetEmission() const { return &emission; }
		const Texture* GetDiffuse() const { return &diffuse; }
		const Texture* GetSpecular() const { return &specular; }
		const float GetShininess() const { return shininess; }

		void SetEmission(Texture emission) { this->emission = emission; }
		void SetDiffuse(Texture diffuse) { this->diffuse = diffuse; }
		void SetSpecular(Texture specular) { this->specular = specular; }
		void SetShininess(float shininess) { this->shininess = shininess; }

	private:
		Texture emission;
		Texture specular;
		Texture diffuse;
		float shininess;
	};
}