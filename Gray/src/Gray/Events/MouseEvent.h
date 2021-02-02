#pragma once

#include "Event.h"

namespace Gray
{

	class MousePressedEvent : public Event
	{
	private:
		MouseButton button;

	public:
		MousePressedEvent(MouseButton button)
		{
			this->button = button;
		}

		std::string ToString()
		{
			std::string buttonName;
			if (button == MouseButton::Left)
				buttonName = "Left";
			else if (button == MouseButton::Right)
				buttonName = "Right";
			else
				buttonName = "Scroll Button";

			return ("MousePressed : " + buttonName);
		}

		MouseButton GetButton()
		{
			return button;
		}

		EVENT_CLASS_TYPE(EventType::MousePressed)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput)
	};


	class MouseReleasedEvent : public Event
	{
	private:
		MouseButton button;

	public:
		MouseReleasedEvent(MouseButton button)
		{
			this->button = button;
		}

		std::string ToString()
		{
			std::string buttonName;
			if (button == MouseButton::Left)
				buttonName = "Left";
			else if (button == MouseButton::Right)
				buttonName = "Right";
			else
				buttonName = "Scroll Button";

			return ("MouseReleased : " + buttonName);
		}

		MouseButton GetButton()
		{
			return button;
		}

		EVENT_CLASS_TYPE(EventType::MouseReleased)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput)
	};


	class MouseMovedEvent : public Event
	{
	private:
		float xPos, yPos;

	public:
		MouseMovedEvent(float xPos, float yPos)
		{
			this->xPos = xPos;
			this->yPos = yPos;
		}

		std::string ToString()
		{
			return "Mouse Moved (to) :  " + std::to_string(xPos) + "," + std::to_string(yPos);
		}

		float GetX()
		{
			return xPos;
		}

		float GetY()
		{
			return yPos;
		}

		EVENT_CLASS_TYPE(EventType::MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};


	class MouseDraggedEvent : public Event
	{
	private:
		float xPos, yPos;

	public:
		MouseDraggedEvent(float xPos, float yPos)
		{
			this->xPos = xPos;
			this->yPos = yPos;
		}

		std::string ToString()
		{
			return "Mouse Dragged (to) :  " + std::to_string(xPos) + "," + std::to_string(yPos);
		}

		float GetX()
		{
			return xPos;
		}

		float GetY()
		{
			return yPos;
		}

		EVENT_CLASS_TYPE(EventType::MouseDragged)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
		{
			this->xOffset = xOffset;
			this->yOffset = yOffset;
		}

		std::string ToString()
		{
			return "Mouse Scrolled : ( x ) " + std::to_string(xOffset) + ", ( y ) " + std::to_string(yOffset);
		}
		
		float GetXOffset()
		{
			return xOffset;
		}

		float GetYOffset()
		{
			return yOffset;
		}

		EVENT_CLASS_TYPE(EventType::MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float xOffset, yOffset;
	};
}
