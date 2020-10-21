#include "grpch.h"

#include "Layer.h"


namespace Gray
{
	void Layer::OnEvent(Event& e)
	{
		if (e.GetCategory() & EventCategoryMouse)
			MouseListener::OnEvent(e);
		else if (e.GetCategory() & EventCategoryKeyboard)
			KeyListener::OnEvent(e);
		else if (e.GetCategory() & EventCategoryWindow)
			WindowListener::OnEvent(e);
		else
		{
			// Event not handled by the above
			GRAY_CORE_WARN("Event" + e.ToString() + " not handled");
		}
	}
}