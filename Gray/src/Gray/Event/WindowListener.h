#pragma once

#include "EventListener.h"
#include "WindowEvent.h"

namespace Gray
{
	class GRAY_API WindowListener : public EventListener
	{
	public:
		void OnEvent(Event& e) const override
		{
			if (e.GetType() == EventType::WindowClosed)
				OnWindowClosed((WindowClosedEvent&)e);

			else if (e.GetType() == EventType::WindowResized)
				OnWindowResized((WindowResizedEvent&)e);
		}

	protected:
		virtual void OnWindowClosed(WindowClosedEvent& e) const { }
		virtual void OnWindowResized(WindowResizedEvent& e) const { }

	};
}