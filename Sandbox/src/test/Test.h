#pragma once

#include "Gray/Graphics/Scene.h"
namespace Test
{
	class Test
	{
	public :
		virtual std::shared_ptr<Gray::Scene> OnInit() = 0;
		virtual void OnUpdate(float dt) = 0;
	};
}