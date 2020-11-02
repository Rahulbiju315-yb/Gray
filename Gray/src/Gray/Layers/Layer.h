#pragma once

#include "Gray/Events/Event.h"
#include "Gray/Events/AllListeners.h"


namespace Gray
{
	class Layer : public AllListeners
	{
	public:
		virtual void OnAttatch() = 0;
		virtual void OnDetatch() = 0;
		virtual void OnUpdate();
		virtual void OnImguiRender()
		{

		}

		void OnEvent(Event& event) override;

	protected:
		float dt, lastTime;
		bool firstFrame;

		void Init();
	};
}
