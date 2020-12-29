#pragma once

#include "LightSource.h"

namespace Gray
{
class PointLight : public LightSource
	{
	public:
		static const uint MAX_LIMIT;

		PointLight();
		void SetUniformsFor(const Shader& shader) override;

	};
}