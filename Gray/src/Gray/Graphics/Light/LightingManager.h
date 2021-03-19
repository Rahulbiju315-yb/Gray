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

		void SetUniformsFor(const Shader& shader) const;
		void ClearList();
		
		PointLight& GetPointLight(uint id);
		SpotLight& GetSpotLight(uint id);
		DirectionalLight& GetDirectionalLight(uint id);

		void RemovePointLight(uint id);
		void RemoveSpotLight(uint id);
		void RemoveDirectionalLight(uint id);
		void RemoveLight(uint id, LightType type);
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