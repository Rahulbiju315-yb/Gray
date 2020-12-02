#pragma once

#include "CameraSource.h"
#include "StaticSource.h"
#include "glm/glm.hpp"

namespace Gray
{
	class SourceFactory
	{
	public:
		static std::shared_ptr<CameraSource> CreateSource(Camera* camera);
		static std::shared_ptr<StaticSource> CreateSource(glm::vec3 pos, glm::vec3 dir=glm::vec3(0.0f));
	};
}