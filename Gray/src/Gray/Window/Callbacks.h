#pragma once

#include "Gray/Events/KeyEvent.h"
#include "Gray/Events/MouseEvent.h"
#include "Gray/Events/WindowEvent.h"
#include "Gray/Events/EventListener.h"


namespace Gray
{
	class Callbacks
	{
	public:
		void AddListener(EventListener* el);
		void PropogateEvent(Event& e);

	private:
		std::vector<EventListener*> eventListeners;

		friend class Window;
	};
}