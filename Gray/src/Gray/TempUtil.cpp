#include "grpch.h"

#include "TempUtil.h"

#include "GLFW/glfw3.h"
#include "Gray/Window/Window.h"

//To be Organized later
namespace Gray
{
	bool TempUtil::isCursoEn = true;

	void TempUtil::DisableCursor()
	{
		glfwSetInputMode(Window::GetWindow()->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		isCursoEn = false;
	}

	void TempUtil::EnableCursor()
	{
		glfwSetInputMode(Window::GetWindow()->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		isCursoEn = true;
	}

	bool TempUtil::IsCursorEnabled()
	{
		return isCursoEn;
	}

	float TempUtil::GetTime()
	{
		return (float)glfwGetTime();
	}
}