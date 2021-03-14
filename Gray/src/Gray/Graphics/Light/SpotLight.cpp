#include "grpch.h"
#include "SpotLight.h"

namespace Gray
{
	static const uint SPOT_MAX_LIMIT = 4;

	SpotLight::SpotLight() 
		: inneCutOff(glm::cos(glm::radians(12.0f))), 
		  outerCutOff(glm::cos(glm::radians(17.0f))),
		  attenuation(1, 0, 0),
		  dir(0, 1, 0),
		  pos(0, 0, 0)
	{
	}

	void SpotLight::SetUniformsFor(const Shader& shader, uint index) const
	{
		std::string prefix = "spotLight[" + std::to_string(index) + "].";

		shader.SetUniform(prefix + "ambient", color.ambient);
		shader.SetUniform(prefix + "diffuse", color.diffuse);
		shader.SetUniform(prefix + "specular", color.specular);
							
		shader.SetUniform(prefix + "dir", dir);
		shader.SetUniform(prefix + "pos", pos);
							
		shader.SetUniform(prefix + "cutOff", inneCutOff);
		shader.SetUniform(prefix + "outerCutOff", outerCutOff);
							
		shader.SetUniform(prefix + "const_term", attenuation.x);
		shader.SetUniform(prefix + "lin_term", attenuation.y);
		shader.SetUniform(prefix + "quad_term", attenuation.z);
	}

}