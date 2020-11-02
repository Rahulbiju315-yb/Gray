#pragma once

#include "Renderable.h"

namespace Gray
{
	class LightSource : public Renderable
	{
	public:
		virtual const glm::vec3& GetColor() = 0;
		virtual void SetColor(glm::vec3 color) = 0;

		virtual void OnUpdate(float dt) override {};
		void OnImguiRender() override = 0;
	};
}