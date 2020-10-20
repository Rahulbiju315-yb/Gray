#include "grpch.h"
#include "Window.h"
#include "WindowsWindow.h"

namespace Gray
{
	Window* Window::Create(const std::string& title, unsigned int width, unsigned int height)
	{
#ifdef GRAY_PLATFORM_WINDOWS
		return new WindowsWindow(title, width, height);
#endif // GRAY_PLATFORM_WINDOWS

	}
}