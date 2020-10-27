#pragma once

#include "Platform/Opengl/Renderer.h"

namespace Gray
{
	class GRAY_API Renderable
	{
	public:
		virtual void OnUpdate(float dt)
		{

		}

		void SetRenderEnabled(bool en) { isRenderEnabled = en; }
		bool GetRenderEnabled() { return isRenderEnabled; }

		static void SetRenderer(Renderer* renderer)
		{
			Renderable::renderer = renderer;
		}
	protected:
		static Renderer* renderer;
		bool isRenderEnabled;
	};
}