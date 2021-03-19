#pragma once

#include "Event.h"
#include "GLFW/glfw3.h"

namespace Gray
{

	class MousePressedEvent : public Event
	{
	public:
		MousePressedEvent(int btn)
			: button(btn)
		{
		}

		int GetButton()
		{
			return button;
		}

		EventType GetType() const override
		{
			return EventType::MousePressed;
		}

	private:
		int button;
	};


	class MouseReleasedEvent : public Event
	{
	public:
		MouseReleasedEvent(int btn)
		{
			button = btn;
		}

		int GetButton()
		{
			return button;
		}

		EventType GetType() const override
		{
			return EventType::MouseReleased;
		}

	private:
		int button;
	};


	class MouseMovedEvent : public Event
	{

	public:
		MouseMovedEvent(float x, float y)
			: xPos(x), yPos(y)
		{
			xPos = x;
			yPos = y;
		}

		float GetX()
		{
			return xPos;
		}

		float GetY()
		{
			return yPos;
		}

		EventType GetType() const override
		{
			return EventType::MouseMoved;
		}

	private:
		float xPos, yPos;

	};


	class MouseDraggedEvent : public Event
	{
	public:
		MouseDraggedEvent(float x, float y)
			: xPos(x), yPos(y)
		{
		}

		float GetX()
		{
			return xPos;
		}

		float GetY()
		{
			return yPos;
		}

		EventType GetType() const override
		{
			return EventType::MouseDragged;
		}

	private:
		float xPos, yPos;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xo, float yo)
			: xOffset(xo), yOffset(yo)
		{
		}
		
		float GetXOffset()
		{
			return xOffset;
		}

		float GetYOffset()
		{
			return yOffset;
		}

		EventType GetType() const override
		{
			return EventType::MouseScrolled;
		}
	private:
		float xOffset, yOffset;
	};
}
