#pragma once

//Renders cube for debug purposes

#include "Gray/Graphics/Renderable.h"

namespace Gray
{
	class DebugCube : public Renderable
	{
	public:
		DebugCube(bool initShader=true, std::shared_ptr<Shader> shader = nullptr, glm::vec3 pos=glm::vec3(0.0f));
		virtual void OnUpdate(float dt) const override;
		virtual void SetUniforms() const override;
		virtual void OnImguiRender() const override;

		void free();

	private:
		Texture tex;
	};
}