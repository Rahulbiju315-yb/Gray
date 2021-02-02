#pragma once


namespace Test
{
	const std::string GUN = "res/models/47-obj/Handgun_obj.obj";
	const std::string BAG = "res/models/backpack/backpack.obj";
	class Test
	{
	public :
		virtual void OnInit() = 0;

		virtual void PreRender(float dt) {}
		virtual void Render(float dt) = 0;
		virtual void PostRender(float dt) {}

		virtual void OnEvent(Gray::Event& e, Gray::EventType type) {}
	};
}