#include "grpch.h"
#include "LightingManager.h"

namespace Gray
{
	int BinarySearch(const std::vector<uint>& vec, uint ele);

	LightingManager::LightingManager()
		: nplID(0),
		  nslID(0),
		  ndlID(0)
	{

	}
	uint LightingManager::AddPointLight(const PointLight& pl)
	{
		pointLights.push_back(pl);
		pointLightIDs.emplace_back(++nplID);
		return nplID;
	}

	uint LightingManager::AddSpotLight(const SpotLight& sl)
	{
		spotLights.push_back(sl);
		spotLightIDs.push_back(++nslID);
		return nslID;

	}

	uint LightingManager::AddDirectionalLight(const DirectionalLight& dl)
	{
		dirLights.push_back(dl);
		dirLightIDs.push_back(++ndlID);
		return ndlID;
	}

	void LightingManager::SetUniformsFor(const Shader& shader)
	{
		static const std::string nrPointLights_var = "nrOfPointLights";
		static const std::string nrSpotLights_var  = "nrOfSpotLights";
		static const std::string nrDirLights_var   = "nrOfDirectionalLights";

		int n_pl = (int)pointLights.size();
		int n_sl = (int)spotLights.size();
		int n_dl = (int)dirLights.size();

		shader.SetUniform(nrPointLights_var, n_pl);
		shader.SetUniform(nrSpotLights_var, n_dl);
		shader.SetUniform(nrDirLights_var, n_sl);

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
		int index = BinarySearch(pointLightIDs, ID);
		assert(index >= 0);
		assert(index < pointLights.size());

		return pointLights[index];
	}

	SpotLight& LightingManager::GetSpotLight(uint ID)
	{
		int index = BinarySearch(spotLightIDs, ID);
		assert(index >= 0);
		assert(index < spotLights.size());

		return spotLights[index];
	}

	DirectionalLight& LightingManager::GetDirectionalLight(uint ID)
	{
		int index = BinarySearch(dirLightIDs, ID);
		assert(index >= 0);
		assert(index < dirLights.size());

		return dirLights[index];
	}

	void LightingManager::RemovePointLight(uint ID)
	{
		int index = BinarySearch(pointLightIDs, ID);
		assert(index >= 0);

		pointLightIDs.erase(pointLightIDs.begin() + index);
		pointLights.erase(pointLights.begin() + index);
	}

	void LightingManager::RemoveSpotLight(uint ID)
	{
		int index = BinarySearch(spotLightIDs, ID);
		assert(index >= 0);

		spotLightIDs.erase(spotLightIDs.begin() + index);
		spotLights.erase(spotLights.begin() + index);
	}

	void LightingManager::RemoveDirectionalLight(uint ID)
	{
		int index = BinarySearch(dirLightIDs, ID);
		assert(index >= 0);

		dirLightIDs.erase(dirLightIDs.begin() + index);
		dirLights.erase(dirLights.begin() + index);
	}


	// Requires unique elements to be meaningful
	int BinarySearch(const std::vector<uint>& vec, uint ele)
	{
		int lb = 0, ub = vec.size() - 1;
		int mid = 0;

		while (lb <= ub)
		{
			mid = (lb + ub) / 2;
			if (vec[mid] == ele)
				return mid;

			else if (vec[mid] > ele)
				ub = mid - 1;

			else
				lb = mid + 1;
		}

		return -1;
	}
}