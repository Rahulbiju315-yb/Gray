#pragma once
#include "Event.h"

namespace Gray
{
	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height)
		{
			this->width = width;
			this->height = height;
		}

		std::string ToString()
		{
			return "Window Resized : " + std::to_string(width) + ", " + std::to_string(height);
		}

		unsigned int GetWidth()
		{
			return width;
		}
		
		unsigned int GetHeight()
		{
			return height;
		}
		
		EVENT_CLASS_TYPE(EventType::WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)

	private:
		unsigned int width, height;
	};
	
	class
		WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent()
		{

		}

		std::string ToString()
		{
			return "Window closed";
		}

		EVENT_CLASS_TYPE(EventType::WindowClosed)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};

}

