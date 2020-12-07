#pragma once
#include "Source.h"
#include "Gray/Graphics/Renderable.h"

namespace Gray
{
	class RenderableSource : public Source
	{
	public:
		RenderableSource(SharedRenderable renderable);
		virtual const glm::vec3& GetPos() override;
		virtual const glm::vec3& GetDir() override;

	private:
		SharedRenderable renderable;
	};
}