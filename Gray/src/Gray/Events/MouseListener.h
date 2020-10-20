#pragma once

#include "EventListener.h"
#include "MouseEvent.h"

namespace Gray
{
	class GRAY_API MouseListener : public EventListener
	{

	public:
		virtual void OnMouseMoved(MouseMovedEvent& e)  { }
		virtual void OnMouseDragged(MouseDraggedEvent& e)  { }
		virtual void OnMousePressed(MousePressedEvent& e)  { }
		virtual void OnMouseReleased(MouseReleasedEvent& e)  { }
		virtual void OnMouseScrolled(MouseScrolledEvent& e)  { }

		void OnEvent(Event& e) override
		{
			if (e.GetType() == EventType::MouseMoved)
				OnMouseMoved((MouseMovedEvent&)e);

			else if (e.GetType() == EventType::MouseDragged)
				OnMouseDragged((MouseDraggedEvent&)e);

			else if (e.GetType() == EventType::MousePressed)
				OnMousePressed((MousePressedEvent&)e);

			else if (e.GetType() == EventType::MouseReleased)
				OnMouseReleased((MouseReleasedEvent&)e);

			else if (e.GetType() == EventType::MouseScrolled)
				OnMouseScrolled((MouseScrolledEvent&)e);

			else
				GRAY_CORE_ERROR("Event passed to MouseListener must be of category mouse!!");

		}
	};
}