#include "grpch.h"

#include "Application.h"
#include "TempUtil.h"
namespace Gray
{
	bool run = true;
	Application* Application::singleton = nullptr;

	Application::Application() 
		: lastTime(-1), window(Window::GetWindow("Gray window", 1200, 700))
	{
		if (!singleton)
		{
			singleton = this;
			Log::Init();
		}
		else
		{
			GRAY_CORE_ERROR("Application already exists!! Cannot create another");
		}

	}

	void Application::Run()
	{
		OnInit();

		while (!window->ShouldBeClosed())
		{
			float dt = GetDT();
			OnUpdate(dt);

			window->BeginImgui();
			OnImguiRender(dt);
			window->EndImgui();

			window->OnUpdate();
		}
	}

	Application* Application::GetApp()
	{
		return singleton;
	}

	void Application::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	float Application::GetDT()
	{
		float dt = 0;
		if (lastTime > 0)
		{
			dt = TempUtil::GetTime() - lastTime;
		}
		else
		{
			dt = 0;
		}
		lastTime = TempUtil::GetTime();

		return dt;
	}

	uint Application::GetWidth()
	{
		return window->GetWidth();
	}
	
	uint Application::GetHeight()
	{
		return window->GetHeight();
	}

	Window* Application::GetWindow()
	{
		return window;
	}
}