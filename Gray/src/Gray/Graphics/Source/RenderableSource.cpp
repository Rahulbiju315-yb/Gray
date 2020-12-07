#include "grpch.h"
#include "RenderableSource.h"

namespace Gray
{
	Gray::RenderableSource::RenderableSource(SharedRenderable renderable) : renderable(renderable)
	{

	}
	const glm::vec3& RenderableSource::GetPos()
	{
		return renderable->GetPos();
	}
	const glm::vec3& RenderableSource::GetDir()
	{
		return renderable->GetDir();
	}
}