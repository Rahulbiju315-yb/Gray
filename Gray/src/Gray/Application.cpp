#include "grpch.h"

#include "Application.h"
#include "TempUtil.h"

namespace Gray
{
	bool run = true;
	Application* Application::app = nullptr;


	Application::Application() : lastTime(-1)
	{
		window = Window::Create("Gray window", 1200, 700);
		window->SetListener(this);

		Application::SetApp(this);

		imguiLayer = new ImguiLayer();
		imguiLayer->OnAttatch();
	}

	Application::~Application()
	{

	}

	void Application::OnWindowClosed(WindowClosedEvent& event) 
	{
		run = false;
		GRAY_INFO("Window closed called");
	}


	void Application::Run()
	{
		Init();
		while (run)
		{
			float dt = GetDT();

			OnUpdate(dt);

			imguiLayer->ImguiBegin();
			OnImguiRender(dt);
			imguiLayer->ImguiEnd();

			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		AllListeners::OnEvent(e);
	}

	Application* Application::GetApp()
	{
		return app;
	}

	void Application::SetApp(Application* app)
	{
		if (Application::app == nullptr)
			Application::app = app;
		else
		{
			GRAY_CORE_ERROR("Application already exists");
		}
	}

	ImGuiContext* Application::GetImguiContext()
	{
		return ImGui::GetCurrentContext();
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

	void* Application::GetProvider()
	{
		return window->GetProvider();
	}

	Window* Application::GetWindow()
	{
		return window;
	}

	WindowProvider Application::GetProviderName()
	{
		return window->GetProviderName();
	}
	//---

}