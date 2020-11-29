#include "grpch.h"

#include "TempUtil.h"

#include "GLFW/glfw3.h"
#include "Gray/Window/Window.h"

//To be Organized later
namespace Gray
{
	void TempUtil::DisableCursor()
	{
		void* window;
		window = Window::GetProvider();
		
		if(Window::GetProviderName() == WindowProvider::GLFW)
			glfwSetInputMode((GLFWwindow*)window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void TempUtil::EnableCursor()
	{
		void* window;
		window = Window::GetProvider();
		
		if(Window::GetProviderName() == WindowProvider::GLFW)
			glfwSetInputMode((GLFWwindow*)window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	float TempUtil::GetTime()
	{
		return (float)glfwGetTime();
	}
}