#pragma once

#include "EventListener.h"
#include "MouseEvent.h"

namespace Gray
{
	class GRAY_API MouseListener : public EventListener
	{

	public:
		virtual void OnMouseMoved(const MouseMovedEvent& e)  { }
		virtual void OnMouseDragged(const MouseDraggedEvent& e)  { }
		virtual void OnMousePressed(const MousePressedEvent& e)  { }
		virtual void OnMouseReleased(const MouseReleasedEvent& e)  { }
		virtual void OnMouseScrolled(const MouseScrolledEvent& e)  { }

		void OnEvent(const Event& e) override
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