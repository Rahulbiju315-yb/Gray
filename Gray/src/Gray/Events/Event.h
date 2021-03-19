#pragma once

namespace Gray
{
	enum class EventType
	{
		MousePressed, MouseReleased, MouseMoved, MouseDragged, MouseScrolled,
		KeyPressed, KeyReleased,
		WindowClosed, WindowResized, WindowFocussed, WindowLostFocus, WindowMoved,
		Other
	};

	class Event
	{
	public:
		virtual EventType GetType() const = 0;
	};

}