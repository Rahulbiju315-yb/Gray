#include "grpch.h"
#include "TempUtil.h"
#include "Gray/Application.h"

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

	float TempUtil::GetTime()
	{
		return glfwGetTime();
	}
}