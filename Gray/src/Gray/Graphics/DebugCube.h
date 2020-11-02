#pragma once

//Renders cube for debug purposes

#include "Gray/Graphics/Renderable.h"

namespace Gray
{
	class DebugCube : public Renderable
	{
	public:
		DebugCube(bool initShader=true, glm::vec3 pos=glm::vec3(0.0f));
		~DebugCube();

		void OnUpdate(float dt) override;
		void OnImguiRender() override;

	private:
		Texture* tex;
	};
}