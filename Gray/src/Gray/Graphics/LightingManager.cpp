#include "grpch.h"
#include "LightingManager.h"

#include "Light/PointLight.h"
#include "Light/DirectionalLight.h"
#include "Light/SpotLight.h"

namespace Gray
{
	LightingManager::LightingManager()
	{
	}

	LightSource* LightingManager::CreateLight(LightType type)
	{
		LightSource* source;
		switch (type)
		{
		case Gray::LightType::PointLight:
			pointLights.push_back(PointLight());
			source = &(pointLights.back());
			break;

		case Gray::LightType::DirectionalLight:
			dirLights.push_back(DirectionalLight());
			source = &(dirLights.back());
			break;

		case Gray::LightType::SpotLight:
			spotLights.push_back(SpotLight());
			source = &(spotLights.back());
			break;

		default:
			source = nullptr;
			break;
		}

		return source;
	}

	void LightingManager::SetUniformsFor(const Shader& shader)
	{
		shader.SetUniform("nrOfPointLights", (int)pointLights.size());
		shader.SetUniform("nrOfDirectionalLights", (int)dirLights.size());
		shader.SetUniform("nrOfSpotLights", (int)spotLights.size());

		for (auto& pl : pointLights)
			pl.SetUniformsFor(shader);

		for (auto& dl : dirLights)
			dl.SetUniformsFor(shader);

		for (auto& sl : spotLights)
			sl.SetUniformsFor(shader);
	}

	std::tuple<int, int, int> LightingManager::GetLightCounts()
	{
		return std::tuple<int, int, int>
			((int)pointLights.size(), 
			(int)dirLights.size(), 
			(int)spotLights.size());
	}
}