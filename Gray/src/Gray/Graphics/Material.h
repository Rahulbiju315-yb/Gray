#pragma once
#include "glm/glm.hpp"
#include "Defaults.h"
#include "Platform/Opengl/Texture.h"

namespace Gray
{
	class Material
	{
	public:
		Material();
		
		void SetDiffuse(WeakRef<Texture> diff);
		void SetSpecular(WeakRef<Texture> spec);
		void SetEmission(WeakRef<Texture> emm);
		void SetShininess(float sh);

		WeakRef<Texture> GetDiffuse() const;
		WeakRef<Texture> GetSpecular() const;
		WeakRef<Texture> GetEmission() const;

		float GetShininess() const;
		uint GetID() const;

	private:
		WeakRef<Texture> diffuse;
		WeakRef<Texture> specular;
		WeakRef<Texture> emission;
		float shininess;

		static uint lastID;
		uint ID;
		friend Material NewMaterial();
	};

}