#include "grpch.h"

#include "Window.h"

#include "WindowsWindow.h"

namespace Gray
{
	void* Window::provider = nullptr;

	Window* Window::Create(const std::string& title, uint width, uint height)
	{
		Window* window;
#ifdef GRAY_PLATFORM_WINDOWS
		window =  new WindowsWindow(title, width, height);
#endif
		if (provider == nullptr)
		{
			GRAY_CORE_ERROR("Window provider not initialized!!!");
		}
		return window;
	}

	WindowProvider Window::GetProviderName()
	{
		return wp;
	}
	void* Window::GetProvider()
	{
		return provider;
	}
}