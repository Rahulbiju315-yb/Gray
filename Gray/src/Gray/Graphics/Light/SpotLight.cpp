#include "grpch.h"
#include "SpotLight.h"

namespace Gray
{
	SpotLight::SpotLight(LightColor color, std::shared_ptr<Source> source, float cutOff, float outerCutOff) :
		cutOff(cutOff), outerCutOff(outerCutOff), 
		LightSource(LightType::SpotLight, color, source)
	{
	}

	void SpotLight::SetUniformsFor(Shader* shader)
	{
		std::string prefix = "spotLight[" + std::to_string(this->index) + "].";

		shader->SetUniform(prefix + "ambient", color.GetAmbient());
		shader->SetUniform(prefix + "diffuse", color.GetDiffuse());
		shader->SetUniform(prefix + "specular", color.GetSpecular());
							
		shader->SetUniform(prefix + "dir", source->GetDir());
		shader->SetUniform(prefix + "pos", source->GetPos());
							
		shader->SetUniform(prefix + "cutOff", cutOff);
		shader->SetUniform(prefix + "outerCutOff", outerCutOff);
							
		shader->SetUniform(prefix + "const_term", k0);
		shader->SetUniform(prefix + "lin_term", k1);
		shader->SetUniform(prefix + "quad_term", k2);
	}

	void SpotLight::SetCutOffs(float outer, float inner)
	{
		this->outerCutOff = outer;
		this->cutOff = inner;
	}

	std::tuple<float, float> SpotLight::GetCutOffs()
	{
		return std::tuple<float, float>(outerCutOff, cutOff);
	}
}