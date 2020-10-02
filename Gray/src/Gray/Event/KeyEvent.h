#pragma once
#include "Gray/Event/Event.h"

namespace Gray
{
	class GRAY_API KeyEvent : public Event
	{
	protected:
		int keyCode;

	public:
		KeyEvent(int keyCode)
		{
			this->handled = false;
			this->keyCode = keyCode;
		}

		int GetKeyCode()
		{
			return keyCode;
		}

		EVENT_CLASS_CATEGORY((EventCategoryKeyboard | EventCategoryInput))
	};


	class GRAY_API KeyPressedEvent : public KeyEvent
	{
	private:
		int repeatCount;

	public:
		KeyPressedEvent(int keyCode, int repeatCount):
			KeyEvent(keyCode)
		{
			this->repeatCount = repeatCount;
		}
		
		std::string ToString() const override
		{
			return ("KeyPressed : " + keyCode);
		}

	    EVENT_CLASS_TYPE(EventType::KeyPressed)
	};


	class GRAY_API KeyReleasedEvent : public KeyEvent
	{

	public:
		KeyReleasedEvent(int keyCode) :
			KeyEvent(keyCode)
		{

		}

		std::string ToString() const override
		{
			return ("KeyReleased : " + keyCode);
		}

		EVENT_CLASS_TYPE(EventType::KeyReleased)
	};
}

