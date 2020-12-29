#pragma once
#include "LightSource.h"

namespace Gray
{
	
	class DirectionalLight : public LightSource
	{
	public:
		static const uint MAX_LIMIT;

		DirectionalLight();
		void SetUniformsFor(const Shader& shader) override;

	};
}