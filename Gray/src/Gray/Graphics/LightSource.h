#pragma once

#include "glm/glm.hpp"
#include "LightColor.h"
#include "Platform/Opengl/Shader.h"
#include "Source/Source.h"

namespace Gray
{
	class LightSource
	{
	public:
		LightSource(LightColor color, std::shared_ptr<Source> source, unsigned int index=0);
		virtual void SetUniformFor(Shader* shader) = 0;

		std::tuple<float, float, float> GetAttenuation();
		void SetAttenuation(float k0, float k1, float k2);

	protected:

		LightColor color;
		std::shared_ptr<Source> source;
		unsigned int index;
		float k0, k1, k2;
	};



	class PointLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		PointLight(LightColor color, std::shared_ptr<Source> source);
		void SetUniformFor(Shader* shader) override;

	private:

	};



	class DirectionalLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		DirectionalLight(LightColor color, std::shared_ptr<Source> source);
		void SetUniformFor(Shader* shader) override;

	private:

	};



	class SpotLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		SpotLight(LightColor color, std::shared_ptr<Source> source,
			float cutOff=glm::cos(glm::radians(12.0f)),
			float outerCutOff=glm::cos(glm::radians(17.0f)));

		void SetUniformFor(Shader* shader) override;
		
	private:

		float cutOff;
		float outerCutOff;
	};
}