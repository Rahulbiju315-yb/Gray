#pragma once

#include "Gray/Events/EventListener.h"

namespace Gray
{
	enum class WindowProvider
	{
		GLFW,
		Unknown
	};

	class Window
	{
	public:	
		static Window* Create(const std::string& title, unsigned int width = 1200, unsigned int height = 700);
		
		virtual void OnInit() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;


		virtual void SetListener(EventListener *listener) = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual const std::string& GetTitle() const = 0;

		virtual void* GetProvider() const = 0;
		static WindowProvider GetProviderName();
	protected:


		static WindowProvider wp;
	};
}