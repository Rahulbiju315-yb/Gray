#pragma once

#include "EventListener.h"
#include "KeyEvent.h"

namespace Gray
{
	class GRAY_API KeyListener : public EventListener
	{
	public:
		virtual void OnKeyPressed(const KeyPressedEvent& e) { }
		virtual void OnKeyReleased(const KeyReleasedEvent& e) { }

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