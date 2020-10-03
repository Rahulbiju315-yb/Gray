#pragma once

#include "EventListener.h"
#include "KeyEvent.h"

namespace Gray
{
	class GRAY_API KeyListener : public EventListener
	{
	protected:
		virtual void OnKeyPressed(KeyPressedEvent& e) const { }
		virtual void OnKeyReleased(KeyReleasedEvent& e) const { }

	public:
		void OnEvent(Event& e) const override
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