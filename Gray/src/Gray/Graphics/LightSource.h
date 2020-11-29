#pragma once

#include "glm/glm.hpp"
#include "LightColor.h"
#include "Platform/Opengl/Shader.h"

namespace Gray
{
	class LightSource
	{
	public:
		LightSource(LightColor color, unsigned int index=0);
		virtual void SetUniformFor(Shader* shader) = 0;

		std::tuple<float, float, float> GetAttenuation();
		void SetAttenuation(float k0, float k1, float k2);

	protected:

		LightColor color;
		unsigned int index;
		float k0, k1, k2;
	};



	class PointLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		PointLight(LightColor color, glm::vec3 pos);
		void SetUniformFor(Shader* shader) override;

	private:

		glm::vec3 pos;
	};



	class DirectionalLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		DirectionalLight(LightColor color, glm::vec3 dir);
		void SetUniformFor(Shader* shader) override;

	private:

		glm::vec3 dir;
	};



	class SpotLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		SpotLight(LightColor color, glm::vec3 pos, glm::vec3 dir,
			float cutOff=glm::cos(glm::radians(45.0f)),
			float outerCutOff=glm::cos(glm::radians(50.0f)));

		void SetUniformFor(Shader* shader) override;
		
	private:

		glm::vec3 pos;
		glm::vec3 dir;
		float cutOff;
		float outerCutOff;
	};
}