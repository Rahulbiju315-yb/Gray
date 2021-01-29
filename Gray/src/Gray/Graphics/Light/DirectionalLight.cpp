#include "grpch.h"
#include "DirectionalLight.h"

namespace Gray
{
	static const uint DIRECTIONAL_MAX_LIMIT = 1;

	DirectionalLight::DirectionalLight() 
		: dir(0, 1, 0)
	{
	}

	void DirectionalLight::SetUniformsFor(const Shader& shader, uint index)
	{
		std::string prefix = "dirLight[" + std::to_string(index) + "].";

		shader.SetUniform(prefix + "ambient", color.GetAmbient());
		shader.SetUniform(prefix + "diffuse", color.GetDiffuse());
		shader.SetUniform(prefix + "specular", color.GetSpecular());
						
		shader.SetUniform(prefix + "dir", dir);
	}
}