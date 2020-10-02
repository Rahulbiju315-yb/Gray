#pragma once
#include <string>
#include "Gray/Core.h"

namespace Gray
{
	enum class GRAY_API EventType
	{
		MousePressed, MouseReleased, MouseMoved, MouseDragged, MouseScrolled,
		KeyPressed, KeyReleased,
		WindowClosed, WindowResized, WindowFocussed, WindowLostFocus, WindowMoved
	};

#define BIT(x) 1 << x 
	enum GRAY_API EventCategory
	{
		EventCategoryWindow = BIT(0),
		EventCategoryKeyboard = BIT(1),
		EventCategoryMouse = BIT(2),
		EventCategoryMouseButton = BIT(3),
		EventCategoryInput = BIT(4)
	};

	enum class GRAY_API MouseButton
	{
		Left,
		Right,
		Middle
	};

#define EVENT_CLASS_TYPE(type) virtual EventType GetType() const override {return type;}\
							   virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategory() const override {return category;}
							   

	class GRAY_API Event
	{
	protected:
		bool handled;

	public:
		virtual EventType GetType() const;
		virtual int GetCategory() const;

		virtual const char* GetName() const;
		virtual std::string ToString() const;

	};

	class GRAY_API EventDispatcher
	{

	};
}