#pragma once

#include "glm/glm.hpp"
#include "LightColor.h"
#include "Platform/Opengl/Shader.h"
#include "Source/Source.h"

namespace Gray
{

	enum class LightType
	{
		PointLight,
		DirectionalLight,
		SpotLight
	};

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



	class PointLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		PointLight(LightColor color, std::shared_ptr<Source> source);
		void SetUniformsFor(Shader* shader) override;

	private:

	};



	class DirectionalLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		DirectionalLight(LightColor color, std::shared_ptr<Source> source);
		void SetUniformsFor(Shader* shader) override;

	private:

	};



	class SpotLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		SpotLight(LightColor color, std::shared_ptr<Source> source,
			float cutOff=glm::cos(glm::radians(12.0f)),
			float outerCutOff=glm::cos(glm::radians(17.0f)));

		void SetUniformsFor(Shader* shader) override;
		
	private:

		float cutOff;
		float outerCutOff;
	};

	typedef std::shared_ptr<LightSource> SharedLightSource;
	typedef std::shared_ptr<PointLight> SharedPointLight;
	typedef std::shared_ptr<DirectionalLight> SharedDirectionalLight;
	typedef std::shared_ptr<SpotLight> SharedSpotLight;
}