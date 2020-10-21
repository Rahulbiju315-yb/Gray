#pragma once

#include "Gray/Events/Event.h"
#include "Gray/Events/AllListeners.h"

namespace Gray
{
	class GRAY_API Layer : public AllListeners
	{
	public:
		virtual void OnAttatch() = 0;
		virtual void OnDetatch() = 0;
		virtual void OnUpdate() = 0;

		virtual void OnEvent(Event& event) override = 0;
	};
}
