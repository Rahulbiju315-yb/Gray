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

	static const unsigned int POINT_MAX_LIMIT = 10;
	static const unsigned int DIRECTIONAL_MAX_LIMIT = 1;
	static const unsigned int SPOT_MAX_LIMIT = 4;

	template<typename T>
	std::shared_ptr<T> CreateLight(std::shared_ptr<Source> s, LightColor color = LightColor());

	class LightSource
	{
	public:
		LightSource(LightType type, LightColor color, std::shared_ptr<Source> source);
		virtual void SetUniformsFor(Shader* shader) = 0;

		std::tuple<float, float, float> GetAttenuation();
		void SetAttenuation(float k0, float k1, float k2);

		void SetIndex(unsigned int index);
		unsigned int GetIndex();

		LightType GetType();
	protected:

		LightColor color;
		std::shared_ptr<Source> source;

		unsigned int index;
		float k0, k1, k2;
		LightType type;
	};

	typedef std::shared_ptr<LightSource> SharedLightSource;
}