#include "grpch.h"
#include "PointLight.h"

namespace Gray
{
	PointLight::PointLight(LightColor color, std::shared_ptr<Source> source):
		LightSource(LightType::PointLight, color, source)
	{
	}

	void PointLight::SetUniformsFor(Shader* shader)
	{
		std::string prefix = "pointLight[" + std::to_string(this->index) + "].";
	
		shader->SetUniform(prefix + "pos", source->GetPos());

		shader->SetUniform(prefix + "ambient", color.GetAmbient());
		shader->SetUniform(prefix + "diffuse", color.GetDiffuse());
		shader->SetUniform(prefix + "specular", color.GetSpecular());
						  
		shader->SetUniform(prefix + "const_term", k0);
		shader->SetUniform(prefix + "lin_term", k1);
		shader->SetUniform(prefix + "quad_term", k2);
	}

}

