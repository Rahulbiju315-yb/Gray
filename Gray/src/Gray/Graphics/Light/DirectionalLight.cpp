#include "grpch.h"
#include "DirectionalLight.h"

namespace Gray
{
	DirectionalLight::DirectionalLight() 
	{
		type = LightType::DirectionalLight;
	}

	void DirectionalLight::SetUniformsFor(const Shader& shader)
	{
		std::string prefix = "dirLight[" + std::to_string(this->index) + "].";

		shader.SetUniform(prefix + "ambient", color.GetAmbient());
		shader.SetUniform(prefix + "diffuse", color.GetDiffuse());
		shader.SetUniform(prefix + "specular", color.GetSpecular());
						
		shader.SetUniform(prefix + "dir", source->GetDir());
	}
}