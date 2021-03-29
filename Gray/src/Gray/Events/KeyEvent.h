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
		KeyPressedEvent(int kc, int rc, int m):
			KeyEvent(kc), repeatCount(rc), mods(m)
		{
		}
		
		int GetRepeat() const
		{
			return repeatCount;
		}

		int GetMods() const
		{
			return mods;
		}

		EventType GetType() const override
		{
			return EventType::KeyPressed;
		}

	private:
		int mods;
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

