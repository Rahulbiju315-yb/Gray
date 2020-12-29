#pragma once

#include "glm/glm.hpp"
#include "LightColor.h"
#include "Platform/Opengl/Shader.h"
#include "Gray/Graphics/Source/Source.h"

namespace Gray
{

	enum class LightType
	{
		PointLight,
		DirectionalLight,
		SpotLight
	};

	static const uint POINT_MAX_LIMIT = 10;
	static const uint DIRECTIONAL_MAX_LIMIT = 1;
	static const uint SPOT_MAX_LIMIT = 4;

	template<class T>
	std::shared_ptr<T> CreateLight(std::shared_ptr<Source> s, LightColor color = LightColor())
	{
		return std::make_shared<T>(color, s);
	}

	class LightSource
	{
	public:
		LightSource();
		virtual void SetUniformsFor(const Shader& shader) = 0;

		std::tuple<float, float, float> GetAttenuation();
		void SetAttenuation(float k0, float k1, float k2);

		void SetIndex(uint index);
		uint GetIndex();

		LightType GetType();

		LightColor color;
		std::unique_ptr<Source> source;

	protected:
		uint index;
		float k0, k1, k2;

		LightType type;
	};

	typedef std::shared_ptr<LightSource> SharedLightSource;
}