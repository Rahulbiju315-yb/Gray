#pragma once

#include "Event.h"
#include "Gray/Log.h"

namespace Gray
{
	class EventListener
	{
	public:
		virtual void OnEvent(Event& e, EventType type) = 0;
	};
}