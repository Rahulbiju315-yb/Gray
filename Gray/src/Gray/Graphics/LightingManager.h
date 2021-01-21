#pragma once

#include "Light/PointLight.h"
#include "Light/DirectionalLight.h"
#include "Light/SpotLight.h"

namespace Gray
{
	class LightingManager
	{
	public:
		LightingManager();

		int CreateLight(LightType type);
		void SetUniformsFor(const Shader& shader);
		void ClearList();

		std::tuple<int, int, int> GetLightCounts(); // point, directional, spot
		LightSource& GetLightSource(int i, LightType type);

	private:
		std::vector<PointLight> pointLights;
		std::vector<DirectionalLight> dirLights;
		std::vector<SpotLight> spotLights;
	};
}