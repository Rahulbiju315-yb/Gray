#include "grpch.h"

#include "Layer.h"
#include "Gray/TempUtil.h"

namespace Gray
{
	void Layer::OnUpdate()
	{
		if (!firstFrame)
		{
			dt = TempUtil::GetTime() - lastTime;
		}
		else
		{
			dt = 0;
			firstFrame = false;
		}
		lastTime = TempUtil::GetTime();
	}

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

	void Layer::Init()
	{
		firstFrame = true;
		dt = 0;
		lastTime = 0;
	}
}