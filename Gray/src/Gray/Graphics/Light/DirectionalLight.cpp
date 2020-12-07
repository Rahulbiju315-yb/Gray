#include "grpch.h"
#include "DirectionalLight.h"

namespace Gray
{
	DirectionalLight::DirectionalLight(LightColor color, std::shared_ptr<Source> source) :
		LightSource(LightType::DirectionalLight, color, source)
	{
	}

	void DirectionalLight::SetUniformsFor(Shader* shader)
	{
		std::string prefix = "DirectionalLight[" + std::to_string(this->index) + "].";

		shader->SetUniform(prefix + "ambient", color.GetAmbient());
		shader->SetUniform(prefix + "diffuse", color.GetDiffuse());
		shader->SetUniform(prefix + "specular", color.GetSpecular());
							
		shader->SetUniform(prefix + "dir", source->GetDir());
	}
}