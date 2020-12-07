#pragma once

#include "LightSource.h"

namespace Gray
{
class PointLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		PointLight(LightColor color, std::shared_ptr<Source> source);
		void SetUniformsFor(Shader* shader) override;

	private:

	};
}