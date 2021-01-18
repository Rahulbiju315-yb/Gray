#include "grpch.h"
#include "Callbacks.h"

namespace Gray
{
	void Callbacks::AddListener(EventListener* el)
	{
		if (el)
			eventListeners.push_back(el);
	}

	void Callbacks::PropogateEvent(Event& e, EventType type)
	{
		for (EventListener* el : eventListeners)
		{
			if (el)
				el->OnEvent(e, type);
		}
	}
}