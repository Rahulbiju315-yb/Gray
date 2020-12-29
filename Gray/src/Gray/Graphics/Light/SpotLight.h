#pragma once
#include "LightSource.h"

namespace Gray
{
	class SpotLight : public LightSource
	{
	public:
		static const uint MAX_LIMIT;

		SpotLight();

		void SetUniformsFor(const Shader& shader) override;

		float inneCutOff;
		float outerCutOff;
	};	
}