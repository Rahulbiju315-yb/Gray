#include "grpch.h"
#include "PointLight.h"

namespace Gray
{
	static const uint POINT_MAX_LIMIT = 10;

	PointLight::PointLight()
		: attenuation(1.0f, 0, 0),
		  pos(0)
	{
	}

	void PointLight::SetUniformsFor(const Shader& shader, uint index)
	{
		std::string prefix = "pointLight[" + std::to_string(index) + "].";
	
		shader.SetUniform(prefix + "pos", pos);
			  
		shader.SetUniform(prefix + "ambient", color.GetAmbient());
		shader.SetUniform(prefix + "diffuse", color.GetDiffuse());
		shader.SetUniform(prefix + "specular", color.GetSpecular());
					  
		shader.SetUniform(prefix + "const_term", attenuation.x);
		shader.SetUniform(prefix + "lin_term", attenuation.y);
		shader.SetUniform(prefix + "quad_term", attenuation.z);
	}

}

