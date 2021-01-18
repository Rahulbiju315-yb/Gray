#include "grpch.h"

#include "TempUtil.h"

#include "GLFW/glfw3.h"
#include "Gray/Window/Window.h"

//To be Organized later
namespace Gray
{
	void TempUtil::DisableCursor()
	{
		glfwSetInputMode(Window::GetWindow()->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void TempUtil::EnableCursor()
	{
		glfwSetInputMode(Window::GetWindow()->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	float TempUtil::GetTime()
	{
		return (float)glfwGetTime();
	}
}