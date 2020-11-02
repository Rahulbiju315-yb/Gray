#include "grpch.h"

#include "TempUtil.h"

#include "GLFW/glfw3.h"

//To be Organized later
namespace Gray
{
	void TempUtil::DisableCursor()
	{
		Application* app = Application::GetApp();

		void* window;
		window = app->GetProvider();
		
		if(app->GetProviderName() == WindowProvider::GLFW)
			glfwSetInputMode((GLFWwindow*)window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void TempUtil::EnableCursor()
	{
		Application* app = Application::GetApp();

		void* window;
		window = app->GetProvider();
		
		if(app->GetProviderName() == WindowProvider::GLFW)
			glfwSetInputMode((GLFWwindow*)window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	float TempUtil::GetTime()
	{
		return (float)glfwGetTime();
	}
}