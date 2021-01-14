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
			: shininess(32.0f), ID(0)
		{
		}

		void SetDiffuse(const Texture* diff) { diffuse = WeakRef<Texture>(diff); }
		void SetSpecular(const Texture* spec) { specular = WeakRef<Texture>(spec); }
		void SetEmission(const Texture* emm) { emission = WeakRef<Texture>(emm); }
		void SetShininess(float sh) { shininess = sh; }

		const Texture* GetDiffuse() const { return diffuse.Get(); }
		const Texture* GetSpecular() const { return specular.Get(); }
		const Texture* GetEmission() const { return emission.Get(); }

		float GetShininess() const { return shininess; }
		uint GetID() const { return ID; }

	private:
		WeakRef<Texture> diffuse;
		WeakRef<Texture> specular;
		WeakRef<Texture> emission;
		float shininess;

		uint ID;
		friend Material CreateMaterial();
	};

}