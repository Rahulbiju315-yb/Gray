#include "grpch.h"
#include "LightingManager.h"

namespace Gray
{
	void LightingManager::AddLight(SharedLightSource light)
	{
		lightSources.push_back(light);

		if (light->GetType() == LightType::PointLight)
		{
			light->SetIndex(countPointLights++);
		}
		else if (light->GetType() == LightType::DirectionalLight)
		{
			light->SetIndex(countDirLights++);
		}
		else if (light->GetType() == LightType::SpotLight)
		{
			light->SetIndex(countSpotLights++);
		}
	}

	bool LightingManager::RemoveLight(SharedLightSource rlight)
	{
		bool found = false;

		for (auto light : lightSources)
		{
			if (rlight == light)
			{
				lightSources.erase(std::remove(lightSources.begin(), lightSources.end(), rlight), lightSources.end());
				if (rlight->GetType() == LightType::PointLight)
					countPointLights++;
				else if (rlight->GetType() == LightType::DirectionalLight)
					countDirLights++;
				else if (rlight->GetType() == LightType::SpotLight)
					countSpotLights++;

				found = true;
			}
			if (found)
				light->SetIndex(light->GetIndex() - 1);
		}
		return false;
	}

	std::vector<std::shared_ptr<LightSource>>::iterator LightingManager::begin()
	{
		return lightSources.begin();
	}

	std::vector<std::shared_ptr<LightSource>>::iterator LightingManager::end()
	{
		return lightSources.end();
	}

	std::tuple<int, int, int> LightingManager::GetLightCounts()
	{
		return std::tuple<int, int, int>(countPointLights, countDirLights, countSpotLights);
	}
}