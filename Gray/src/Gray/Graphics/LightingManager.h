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

		LightSource* CreateLight(LightType type);
		void SetUniformsFor(const Shader& shader);

		std::tuple<int, int, int> GetLightCounts(); // point, directional, spot

	private:
		std::vector<PointLight> pointLights;
		std::vector<DirectionalLight> dirLights;
		std::vector<SpotLight> spotLights;
	};
}