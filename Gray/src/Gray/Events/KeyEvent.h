#pragma once
#include "Gray/Events/Event.h"
#include "KeyCodes.h"

namespace Gray
{
	class GRAY_API KeyEvent : public Event
	{
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

	protected:
		int keyCode;
	};


	class GRAY_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount):
			KeyEvent(keyCode)
		{
			this->repeatCount = repeatCount;
		}
		
		int GetRepeat()
		{
			return repeatCount;
		}

		std::string ToString() const override
		{
			return ("KeyPressed : " + keyCode);
		}

	    EVENT_CLASS_TYPE(EventType::KeyPressed)

	private:
		int repeatCount;
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

