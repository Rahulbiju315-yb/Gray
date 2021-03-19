#pragma once

#include "Gray/Events/Event.h"

namespace Gray
{
	class KeyEvent : public Event
	{
	public:
		KeyEvent(int kc)
			: keyCode(kc)
		{
		}

		int GetKeyCode() const
		{
			return keyCode;
		}

	protected:
		int keyCode;
	};


	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int kc, int rc):
			KeyEvent(kc), repeatCount(rc)
		{
		}
		
		int GetRepeat() const
		{
			return repeatCount;
		}

		EventType GetType() const override
		{
			return EventType::KeyPressed;
		}

	private:
		int repeatCount;
	};


	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode) :
			KeyEvent(keyCode)
		{
		}

		EventType GetType() const override
		{
			return EventType::KeyReleased;
		}
	};
}

