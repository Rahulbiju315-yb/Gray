#pragma once

#include "LightSource.h"
#include "Renderable.h"

namespace Gray
{
	class LightSourceOpengl : public LightSource
	{
	public:
		LightSourceOpengl(glm::vec3 color = glm::vec3(1.0f));
		~LightSourceOpengl();

		void SetColor(glm::vec3 color) override;
		const glm::vec3& GetColor() override;

		void OnUpdate(float dt) override;
		void OnImguiRender() override;

	private:
		glm::vec3 color;
	};
}