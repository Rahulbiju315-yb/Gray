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

	int LightingManager::CreateLight(LightType type)
	{
		int index = -1;
		switch (type)
		{
		case Gray::LightType::PointLight:
			pointLights.push_back(PointLight());
			index = (int)pointLights.size();
			break;

		case Gray::LightType::DirectionalLight:
			dirLights.push_back(DirectionalLight());
			index = (int)dirLights.size();
			break;

		case Gray::LightType::SpotLight:
			spotLights.push_back(SpotLight());
			index = (int)spotLights.size();
			break;

		default:
			break;
		}

		return index - 1;
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

	void LightingManager::ClearList()
	{
		pointLights.clear();
		dirLights.clear();
		spotLights.clear();
	}

	std::tuple<int, int, int> LightingManager::GetLightCounts()
	{
		return std::tuple<int, int, int>
			((int)pointLights.size(), 
			(int)dirLights.size(), 
			(int)spotLights.size());
	}

	LightSource& LightingManager::GetLightSource(int i, LightType type)
	{
		if (type == LightType::PointLight)
		{
			assert(i < pointLights.size());
			return pointLights[i];
		}
		else if (type == LightType::DirectionalLight)
		{
			assert(i < dirLights.size());
			return dirLights[i];
		}
		else
		{
			assert(i < spotLights.size());
			return spotLights[i];
		}
	}
}