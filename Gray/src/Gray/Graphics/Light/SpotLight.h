#pragma once
#include "LightSource.h"

namespace Gray
{
	class SpotLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		SpotLight(LightColor color, std::shared_ptr<Source> source,
			float cutOff=glm::cos(glm::radians(12.0f)),
			float outerCutOff=glm::cos(glm::radians(17.0f)));

		void SetUniformsFor(Shader* shader) override;

		void SetCutOffs(float outer, float inner);
		std::tuple<float, float> GetCutOffs();
	private:

		float cutOff;
		float outerCutOff;
	};	
}