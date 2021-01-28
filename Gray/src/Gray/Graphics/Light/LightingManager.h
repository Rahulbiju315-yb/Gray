#pragma once

#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

#include "Platform/Opengl/Shader.h"
namespace Gray
{
	enum class LightType
	{
		PointLight,
		SpotLight,
		DirectionalLight
	};

	class LightingManager
	{
	public:
		LightingManager();

		uint AddPointLight(const PointLight& pl = PointLight());
		uint AddSpotLight(const SpotLight& sl = SpotLight());
		uint AddDirectionalLight(const DirectionalLight& dl = DirectionalLight());

		void SetUniformsFor(const Shader& shader);
		void ClearList();
		
		PointLight& GetPointLight(uint ID);
		SpotLight& GetSpotLight(uint ID);
		DirectionalLight& GetDirectionalLight(uint ID);

		void RemovePointLight(uint ID);
		void RemoveSpotLight(uint ID);
		void RemoveDirectionalLight(uint ID);

	private:
		std::vector<PointLight> pointLights;
		std::vector<uint> pointLightIDs;

		std::vector<SpotLight> spotLights;
		std::vector<uint> spotLightIDs;
 
		std::vector<DirectionalLight> dirLights;
		std::vector<uint> dirLightIDs;

		uint nplID;
		uint ndlID;
		uint nslID;
	};
}