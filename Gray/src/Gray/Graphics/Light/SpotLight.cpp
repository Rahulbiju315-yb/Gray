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

	void SpotLight::SetUniformsFor(const Shader& shader, uint index)
	{
		std::string prefix = "spotLight[" + std::to_string(index) + "].";

		shader.SetUniform(prefix + "ambient", color.GetAmbient());
		shader.SetUniform(prefix + "diffuse", color.GetDiffuse());
		shader.SetUniform(prefix + "specular", color.GetSpecular());
							
		shader.SetUniform(prefix + "dir", pos);
		shader.SetUniform(prefix + "pos", dir);
							
		shader.SetUniform(prefix + "cutOff", inneCutOff);
		shader.SetUniform(prefix + "outerCutOff", outerCutOff);
							
		shader.SetUniform(prefix + "const_term", attenuation.x);
		shader.SetUniform(prefix + "lin_term", attenuation.y);
		shader.SetUniform(prefix + "quad_term", attenuation.z);
	}

}