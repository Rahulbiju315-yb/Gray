#pragma once
#include "Gray/Core.h"

namespace Gray
{
	enum class EventType
	{
		MousePressed, MouseReleased, MouseMoved, MouseDragged, MouseScrolled,
		KeyPressed, KeyReleased,
		WindowClosed, WindowResized, WindowFocussed, WindowLostFocus, WindowMoved
	};

#define BIT(x) 1 << x 
	enum EventCategory
	{
		EventCategoryWindow = BIT(0),
		EventCategoryKeyboard = BIT(1),
		EventCategoryMouse = BIT(2),
		EventCategoryMouseButton = BIT(3),
		EventCategoryInput = BIT(4)
	};

	enum class MouseButton
	{
		Left,
		Right,
		Middle
	};

#define EVENT_CLASS_TYPE(type) virtual EventType GetType() const override {return type;}\
							   virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategory() const override {return category;}
							   

	class Event
	{
	public:
		virtual EventType GetType() const = 0;
		virtual int GetCategory() const = 0;

		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); };

		bool IsHandled()
		{
			return handled;
		}

		void SetHandled(bool handled)
		{
			this->handled = handled;
		}
	protected:
		bool handled;
	};

}