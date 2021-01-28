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
		pointLightIDs.push_back(nplID++);
		return nplID - 1;
	}

	uint LightingManager::AddSpotLight(const SpotLight& sl)
	{
		spotLights.push_back(sl);
		spotLightIDs.push_back(nslID++);
		return nslID - 1;

	}

	uint LightingManager::AddDirectionalLight(const DirectionalLight& dl)
	{
		dirLights.push_back(dl);
		dirLightIDs.push_back(ndlID++);
		return ndlID - 1;
	}

	void LightingManager::SetUniformsFor(const Shader& shader)
	{
		int n_pl = (int)pointLights.size();
		int n_sl = (int)spotLights.size();
		int n_dl = (int)dirLights.size();

		shader.SetUniform("nrOfPointLights", n_pl);
		shader.SetUniform("nrOfDirectionalLights", n_dl);
		shader.SetUniform("nrOfSpotLights", n_sl);

		for (int i = 0; i < n_pl; i++)
		{
			pointLights[i].SetUniformsFor(shader, i);
		}

		for (int i = 0; i < n_sl; i++)
		{
			spotLights[i].SetUniformsFor(shader, i);
		}

		for (int i = 0; i < n_dl; i++)
		{
			dirLights[i].SetUniformsFor(shader, i);
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