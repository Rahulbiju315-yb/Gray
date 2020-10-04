#pragma once

#include "grpch.h"
#include "Gray/Core.h"
#include "Gray/Event/EventListener.h"

namespace Gray
{
	struct GRAY_API WindowProperties
	{
		unsigned int width;
		unsigned int height;
		std::string title;

		WindowProperties(const std::string& title="Gray",
			unsigned int width=1200, unsigned int height=720)
		{
			this->width = width;
			this->height = height;
			this->title = title;
		}
	};

	class GRAY_API Window : public EventListener
	{
	public:
		virtual void SetVSync(bool enabled) const = 0;
		virtual bool IsVSync() const = 0;

		virtual WindowProperties GetWindowProperties() const = 0;
		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}