#include "grpch.h"
#include "DirectionalLight.h"

namespace Gray
{
	static const uint DIRECTIONAL_MAX_LIMIT = 1;

	DirectionalLight::DirectionalLight() 
		: dir(0, 1, 0)
	{
	}

	void DirectionalLight::SetUniformsFor(const Shader& shader, uint index) const
	{
		std::string prefix = "dirLight[" + std::to_string(index) + "].";

		shader.SetUniform(prefix + "ambient", color.ambient);
		shader.SetUniform(prefix + "diffuse", color.diffuse);
		shader.SetUniform(prefix + "specular", color.specular);
						
		shader.SetUniform(prefix + "dir", dir);
	}
}