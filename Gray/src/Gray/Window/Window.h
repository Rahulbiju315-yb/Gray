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
		static Window* Create(const std::string& title, uint width = 1200, uint height = 700);
		
		virtual void OnInit() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;


		virtual void SetListener(EventListener *listener) = 0;

		virtual uint GetWidth() const = 0;
		virtual uint GetHeight() const = 0;
		virtual const std::string& GetTitle() const = 0;

		static WindowProvider GetProviderName();
		static void* GetProvider();

	protected:

		static WindowProvider wp;
		static void* provider;
	};
}