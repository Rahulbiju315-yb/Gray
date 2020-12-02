#include "grpch.h"

#include "LightSource.h"

namespace Gray
{
	const unsigned int PointLight::MAX_LIMIT = 10;
	const unsigned int DirectionalLight::MAX_LIMIT = 1;
	const unsigned int SpotLight::MAX_LIMIT = 4;

	
	LightSource::LightSource(LightType type,LightColor color, std::shared_ptr<Source> source) : 
		color(color), source(source),
		k0(Defaults::DEFAULT_K0), k1(Defaults::DEFAULT_K1), k2(Defaults::DEFAULT_K2),
		index(0), type(type)
	{
	}

	std::tuple<float, float, float> LightSource::GetAttenuation()
	{
		return std::make_tuple(k0, k1, k2);
	}

	void LightSource::SetAttenuation(float k0, float k1, float k2)
	{
		this->k0 = k0;
		this->k1 = k1;
		this->k2 = k2;
	}

	void LightSource::SetIndex(unsigned int index)
	{
		this->index = index;
	}

	unsigned int LightSource::GetIndex()
	{
		return index;
	}

	LightType LightSource::GetType() { return type; }

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
	
}
