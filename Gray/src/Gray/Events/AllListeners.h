#pragma once

#include "grpch.h"

namespace Gray
{
	class AllListeners : public MouseListener, public KeyListener, public WindowListener, public EventListener
	{
		virtual void OnEvent(Event& e) override
		{

		}
	};
}