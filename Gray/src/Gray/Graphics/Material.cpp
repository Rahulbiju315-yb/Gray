#include "grpch.h"
#include "Material.h"

namespace Gray
{
	uint Material::lastID = 0;

	Material::Material()
		: diffuse(EmptyTex()),
		specular(EmptyTex()),
		emission(EmptyTex()),
		shininess(32.0f),
		ID(++lastID)
	{
	}

	void Material::SetDiffuse(WeakRef<Texture> diff) { diffuse = diff; }
	
	void Material::SetSpecular(WeakRef<Texture> spec) { specular = spec; }
	
	void Material::SetEmission(WeakRef<Texture> emm) { emission = emm; }
	
	void Material::SetShininess(float sh) { shininess = sh; }
	
	WeakRef<Texture> Material::GetDiffuse() const { return diffuse.Get(); }
	
	WeakRef<Texture> Material::GetSpecular() const { return specular.Get(); }
	
	WeakRef<Texture> Material::GetEmission() const { return emission.Get(); }
	
	float Material::GetShininess() const { return shininess; }
	
	uint Material::GetID() const { return ID; }
}