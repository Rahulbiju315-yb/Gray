#pragma once

#include "Light/LightSource.h"

namespace Gray
{
	class LightingManager
	{
	public:
		LightingManager();

		void AddLight(SharedLightSource light);
		bool RemoveLight(SharedLightSource light);

		std::vector<SharedLightSource>::iterator begin();
		std::vector<SharedLightSource>::iterator end();

		std::tuple<int, int, int> GetLightCounts(); // point, directional, spot
	private:
		int countPointLights;
		int countDirLights;
		int countSpotLights;

		std::vector<SharedLightSource> lightSources;
	};
}