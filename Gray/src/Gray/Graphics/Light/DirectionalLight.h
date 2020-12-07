#pragma once
#include "LightSource.h"

namespace Gray
{
	
	class DirectionalLight : public LightSource
	{
	public:
		static const unsigned int MAX_LIMIT;

		DirectionalLight(LightColor color, std::shared_ptr<Source> source);
		void SetUniformsFor(Shader* shader) override;

	private:

	};
}