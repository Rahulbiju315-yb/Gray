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
			: diffuse(EmptyTex()),
			  specular(EmptyTex()),
			  emission(EmptyTex()),
			  shininess(32.0f), 
			  ID(0)
		{
		}

		void SetDiffuse(WeakRef<Texture> diff) { diffuse = diff; }
		void SetSpecular(WeakRef<Texture> spec) { specular = spec; }
		void SetEmission(WeakRef<Texture> emm) { emission = emm; }
		void SetShininess(float sh) { shininess = sh; }

		WeakRef<Texture> GetDiffuse() const { return diffuse.Get(); }
		WeakRef<Texture> GetSpecular() const { return specular.Get(); }
		WeakRef<Texture> GetEmission() const { return emission.Get(); }

		float GetShininess() const { return shininess; }
		uint GetID() const { return ID; }

	private:
		WeakRef<Texture> diffuse;
		WeakRef<Texture> specular;
		WeakRef<Texture> emission;
		float shininess;

		uint ID;
		friend Material NewMaterial();
	};

}