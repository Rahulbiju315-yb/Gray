#include "grpch.h"
#include "SpotLight.h"

namespace Gray
{
	SpotLight::SpotLight() :
		inneCutOff(glm::cos(glm::radians(12.0f))), outerCutOff(glm::cos(glm::radians(17.0f)))
	{
		type = LightType::SpotLight;
	}

	void SpotLight::SetUniformsFor(const Shader& shader)
	{
		std::string prefix = "spotLight[" + std::to_string(this->index) + "].";

		shader.SetUniform(prefix + "ambient", color.GetAmbient());
		shader.SetUniform(prefix + "diffuse", color.GetDiffuse());
		shader.SetUniform(prefix + "specular", color.GetSpecular());
							
		shader.SetUniform(prefix + "dir", source->GetDir());
		shader.SetUniform(prefix + "pos", source->GetPos());
							
		shader.SetUniform(prefix + "cutOff", inneCutOff);
		shader.SetUniform(prefix + "outerCutOff", outerCutOff);
							
		shader.SetUniform(prefix + "const_term", k0);
		shader.SetUniform(prefix + "lin_term", k1);
		shader.SetUniform(prefix + "quad_term", k2);
	}

}