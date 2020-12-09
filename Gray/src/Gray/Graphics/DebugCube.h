#pragma once

//Renders cube for debug purposes

#include "Gray/Graphics/Renderable.h"

namespace Gray
{
	class DebugCube : public Renderable
	{
	public:
		DebugCube();
		DebugCube(std::shared_ptr<Shader> shader, RenderData data);

		virtual void OnUpdate(float dt) const override;
		virtual void SetUniforms() const override;
		virtual void OnImguiRender() const override;

	private:
		Texture tex;
	};
}