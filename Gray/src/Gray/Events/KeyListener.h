#pragma once

#include "EventListener.h"
#include "KeyEvent.h"

namespace Gray
{
	class KeyListener : virtual public EventListener
	{
	public:
		virtual void OnKeyPressed(KeyPressedEvent& e) { }
		virtual void OnKeyReleased(KeyReleasedEvent& e) { }

		void OnEvent(Event& e) override
		{
			if (e.GetType() == EventType::KeyPressed)
				OnKeyPressed((KeyPressedEvent&)e);

			else if (e.GetType() == EventType::KeyReleased)
				OnKeyReleased((KeyReleasedEvent&)e);

			else
				GRAY_CORE_ERROR("Event passed to KeyListener must be of category keyboard!!");
		}
	};
}