#pragma once

#include "grpch.h"

#include "Gray/Events/EventListener.h"
#include "Gray/Events/WindowListener.h"
#include "Gray/Events/MouseListener.h"
#include "Gray/Events/KeyListener.h"

#include "Gray/Events/KeyEvent.h"
#include "Gray/Events/MouseEvent.h"
#include "Gray/Events/WindowEvent.h"

namespace Gray
{
	class AllListeners : public virtual EventListener, public MouseListener, public KeyListener, public WindowListener
	{
	public:
		virtual void OnEvent(Event& e) override
		{
			if(e.GetCategory() & EventCategoryMouse)
				MouseListener::OnEvent(e);

			else if(e.GetCategory() & EventCategoryKeyboard)
				KeyListener::OnEvent(e);

			else if(e.GetCategory() & EventCategoryWindow)
				WindowListener::OnEvent(e);
		}

	private:
		using MouseListener::OnEvent;
		using KeyListener::OnEvent;
		using WindowListener::OnEvent;
	};
}