#pragma once

#include "Gray/Graphics/Scene.h"
namespace Test
{
	class Test
	{
	public :
		virtual std::shared_ptr<Gray::Scene> OnInit(Gray::RenderLayer* renderLayer) = 0;
	};
}