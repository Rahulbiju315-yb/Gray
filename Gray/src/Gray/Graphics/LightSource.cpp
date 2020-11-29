#include "grpch.h"

#include "LightSource.h"

namespace Gray
{
	const unsigned int PointLight::MAX_LIMIT = 10;
	const unsigned int DirectionalLight::MAX_LIMIT = 1;
	const unsigned int SpotLight::MAX_LIMIT = 4;

	LightSource::LightSource(LightColor color, unsigned int index) : 
		color(color),
		k0(Defaults::DEFAULT_K0), k1(Defaults::DEFAULT_K1), k2(Defaults::DEFAULT_K2),
		index(index)
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

	PointLight::PointLight(LightColor color, glm::vec3 pos):
		pos(pos), LightSource(color)
	{
	}

	void PointLight::SetUniformFor(Shader* shader)
	{
		shader->SetUniform("pointLight[" + std::to_string(index) + "].ambient", color.GetAmbient());
		shader->SetUniform("pointLight[" + std::to_string(index) + "].diffuse", color.GetDiffuse());
		shader->SetUniform("pointLight[" + std::to_string(index) + "].specular", color.GetSpecular());

		shader->SetUniform("pointLight[" + std::to_string(index) + "].const_term", k0);
		shader->SetUniform("pointLight[" + std::to_string(index) + "].lin_term", k1);
		shader->SetUniform("pointLight[" + std::to_string(index) + "].quad_term", k2);
	}

	DirectionalLight::DirectionalLight(LightColor color, glm::vec3 dir) :
		dir(dir), LightSource(color)
	{
	}

	void DirectionalLight::SetUniformFor(Shader* shader)
	{
		shader->SetUniform("dirLight.ambient", color.GetAmbient());
		shader->SetUniform("dirLight.diffuse", color.GetDiffuse());
		shader->SetUniform("dirLight.specular", color.GetSpecular());
		shader->SetUniform("dirLight.dir", dir);
	}

	SpotLight::SpotLight(LightColor color, glm::vec3 pos, glm::vec3 dir, float cutOff, float outerCutOff) :
		pos(pos), dir(dir), cutOff(cutOff), outerCutOff(outerCutOff), LightSource(color)
	{
	}

	void SpotLight::SetUniformFor(Shader* shader)
	{
		shader->SetUniform("spotLight[" + std::to_string(index) + "].ambient", color.GetAmbient());
		shader->SetUniform("spotLight[" + std::to_string(index) + "].diffuse", color.GetDiffuse());
		shader->SetUniform("spotLight[" + std::to_string(index) + "].specular", color.GetSpecular());
		shader->SetUniform("spotLight[" + std::to_string(index) + "].dir", dir);
		shader->SetUniform("spotLight[" + std::to_string(index) + "].pos", pos);
		shader->SetUniform("spotLight[" + std::to_string(index) + "].cutOff", cutOff);
		shader->SetUniform("spotLight[" + std::to_string(index) + "].outerCutOff", outerCutOff);

		shader->SetUniform("spotLight[" + std::to_string(index) + "].const_term", k0);
		shader->SetUniform("spotLight[" + std::to_string(index) + "].lin_term", k1);
		shader->SetUniform("spotLight[" + std::to_string(index) + "].quad_term", k2);
	}
	
}
