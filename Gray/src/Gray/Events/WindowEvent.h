#pragma once
#include "Event.h"

namespace Gray
{
	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(uint w, uint h)
			: width(w), height(h)
		{
		}

		uint GetWidth()
		{
			return width;
		}
		
		uint GetHeight()
		{
			return height;
		}

		EventType GetType() const override
		{
			return EventType::WindowResized;
		}

	private:
		uint width, height;
	};
	
	class WindowClosedEvent : public Event
	{
	public:
		EventType GetType() const override
		{
			return EventType::WindowClosed;
		}
	};

}

