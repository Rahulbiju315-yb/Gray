#include "grpch.h"
#include "SourceFactory.h"

namespace Gray
{
	std::shared_ptr<CameraSource> CreateSource(Camera* camera)
	{
		return std::make_shared<CameraSource>(camera);
	}

	std::shared_ptr<RenderableSource> CreateSource(SharedRenderable renderable)
	{
		return std::make_shared<RenderableSource>(renderable);
	}

	std::shared_ptr<StaticSource> CreateSource(glm::vec3 pos, glm::vec3 dir)
	{
		return std::make_shared<StaticSource>(pos, dir);
	}
}