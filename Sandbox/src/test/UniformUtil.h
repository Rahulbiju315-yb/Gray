#pragma once

#include "Gray/Graphics/Material.h"
#include "Platform/Opengl/Shader.h"

#include "glm/glm.hpp"

namespace Test
{

	void SetMaterialUniform(const Gray::Material& material, const Gray::Shader& shader)
	{
		material.GetDiffuse()->Bind(1);
		material.GetSpecular()->Bind(2);
		material.GetEmission()->Bind(3);

		shader.SetUniform("material.diffuse", 1);
		shader.SetUniform("material.specular", 2);
		shader.SetUniform("material.emission", 3);
		shader.SetUniform("material.shininess", material.GetShininess());
	}
}