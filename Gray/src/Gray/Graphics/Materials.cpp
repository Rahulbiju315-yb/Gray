#include "grpch.h"
#include "Material.h"

namespace Gray
{
	inline Gray::Material::Material()
		: diffuse(EmptyTex()),
		specular(EmptyTex()),
		emission(EmptyTex()),
		shininess(32.0f),
		ID(0)
	{
	}

	inline void Gray::Material::SetDiffuse(WeakRef<Texture> diff) { diffuse = diff; }

	inline void Gray::Material::SetSpecular(WeakRef<Texture> spec) { specular = spec; }

	inline void Gray::Material::SetEmission(WeakRef<Texture> emm) { emission = emm; }

	inline void Gray::Material::SetShininess(float sh) { shininess = sh; }

	inline WeakRef<Texture> Gray::Material::GetDiffuse() const { return diffuse.Get(); }

	inline WeakRef<Texture> Gray::Material::GetSpecular() const { return specular.Get(); }

	inline WeakRef<Texture> Gray::Material::GetEmission() const { return emission.Get(); }

	inline float Gray::Material::GetShininess() const { return shininess; }

	inline uint Gray::Material::GetID() const { return ID; }
}