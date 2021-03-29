#include "grpch.h"
#include "LightingManager.h"
#include "Gray/Algo/Search.h"

namespace Gray
{

	LightingManager::LightingManager()
	{

	}

	uint LightingManager::AddPointLight(const PointLight& pl)
	{
		static uint nplID = 0;
		pointLights.push_back(pl);
		pointLightIDs.emplace_back(++nplID);

		return nplID;
	}

	uint LightingManager::AddSpotLight(const SpotLight& sl)
	{
		static uint nslID = 0;
		spotLights.push_back(sl);
		spotLightIDs.push_back(++nslID);

		return nslID;

	}

	uint LightingManager::AddDirectionalLight(const DirectionalLight& dl)
	{
		static uint ndlID = 0;
		dirLights.push_back(dl);
		dirLightIDs.push_back(++ndlID);

		return ndlID;
	}

	void LightingManager::SetUniformsFor(const Shader& shader) const
	{
		static const std::string nrPointLights_var = "nrOfPointLights";
		static const std::string nrSpotLights_var  = "nrOfSpotLights";
		static const std::string nrDirLights_var   = "nrOfDirectionalLights";

		int n_pl = static_cast<int>(pointLights.size());
		int n_sl = static_cast<int>(spotLights.size());
		int n_dl = static_cast<int>(dirLights.size());

		shader.SetUniform(nrPointLights_var, n_pl);
		shader.SetUniform(nrSpotLights_var, n_sl);
		shader.SetUniform(nrDirLights_var, n_dl);

		int i = 0;
		for (const PointLight& pl : pointLights)
		{
			pl.SetUniformsFor(shader, i++);
		}

		i = 0;
		for (const SpotLight& sl : spotLights)
		{
			sl.SetUniformsFor(shader, i++);
		}

		i = 0;
		for (const DirectionalLight& dl : dirLights)
		{
			dl.SetUniformsFor(shader, i++);
		}
	}

	void LightingManager::ClearList()
	{
		pointLights.clear();
		dirLights.clear();
		spotLights.clear();
	}

	PointLight& LightingManager::GetPointLight(uint ID)
	{
		int index = Bsearch(pointLightIDs, ID);
		assert(index >= 0);
		assert(index < pointLights.size());

		return pointLights[index];
	}

	SpotLight& LightingManager::GetSpotLight(uint ID)
	{
		int index = Bsearch(spotLightIDs, ID);
		assert(index >= 0);
		assert(index < spotLights.size());

		return spotLights[index];
	}

	DirectionalLight& LightingManager::GetDirectionalLight(uint ID)
	{
		int index = Bsearch(dirLightIDs, ID);
		assert(index >= 0);
		assert(index < dirLights.size());

		return dirLights[index];
	}

	void LightingManager::RemovePointLight(uint ID)
	{
		int index = Bsearch(pointLightIDs, ID);
		assert(index >= 0);

		pointLightIDs.erase(pointLightIDs.begin() + index);
		pointLights.erase(pointLights.begin() + index);
	}

	void LightingManager::RemoveSpotLight(uint ID)
	{
		int index = Bsearch(spotLightIDs, ID);
		assert(index >= 0);

		spotLightIDs.erase(spotLightIDs.begin() + index);
		spotLights.erase(spotLights.begin() + index);
	}

	void LightingManager::RemoveDirectionalLight(uint ID)
	{
		int index = Bsearch(dirLightIDs, ID);
		assert(index >= 0);

		dirLightIDs.erase(dirLightIDs.begin() + index);
		dirLights.erase(dirLights.begin() + index);
	}

	void LightingManager::RemoveLight(uint id, LightType type)
	{
		if (type == LightType::PointLight)
			RemovePointLight(id);

		else if (type == LightType::SpotLight)
			RemoveSpotLight(id);

		else if (type == LightType::DirectionalLight)
			RemoveDirectionalLight(id);
	}

}