#pragma once

#include "Model.h"
#include "Gray/Graphics/Renderable.h"
#include "Gray/Graphics/Transformable.h"

namespace Gray
{
	class RenderableModel : public Renderable, public Transformable
	{
	public:
		RenderableModel(std::shared_ptr<Model> model);

		inline virtual Transform& GetTransform();
		virtual void OnUpdate(float dt) const override;

	private:
		std::shared_ptr<Model> model;
		Transform transform;
	};
}