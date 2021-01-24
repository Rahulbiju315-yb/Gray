#pragma once

#include "Gray/Graphics/Scene.h"

namespace Test
{
	const std::string GUN = "res/models/47-obj/Handgun_obj.obj";
	const std::string BAG = "res/models/backpack/backpack.obj";
	class Test
	{
	public :
		virtual Gray::Scene* OnInit() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnImguiRender(float dt) {}
		virtual void OnEvent(Gray::Event& e, Gray::EventType type) {}
	};
}