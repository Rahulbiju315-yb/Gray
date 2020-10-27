#include "grpch.h"
#include "Application.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Window/Window.h"

namespace Gray
{
	bool run = true;
	Application* Application::app = nullptr;


	Application::Application()
	{
		window = Window::Create("Gray window", 1200, 700);
		window->SetListener((AllListeners*)this);

		Application::SetApp(this);
	}

	Application::~Application()
	{

	}

	//---
	
	void Application::AddLayer(Layer* l)
	{
		l->OnAttatch();
		ls.PushLayer(l);
	}

	bool Application::RemoveLayer(Layer* l)
	{
		return ls.RemoveLayer(l);
	}

	bool Application::RemoveLayerAt(int i)
	{
		return ls.RemoveLayer(ls.LayerAt(i));
	}

	//---



	//---

	void Application::OnWindowClosed(WindowClosedEvent& event) 
	{
		run = false;
		GRAY_INFO("Window closed called");
	}

	//---

	

	//---

	void Application::Run()
	{
		while (run)
		{
			//Clear();

			for (Layer *layer : ls)
				layer->OnUpdate();

			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		if(e.GetCategory() & EventCategoryMouse)
			MouseListener::OnEvent(e);

		else if(e.GetCategory() & EventCategoryKeyboard)
			KeyListener::OnEvent(e);

		else if(e.GetCategory() & EventCategoryWindow)
			WindowListener::OnEvent(e);


		for (std::vector<Layer*>::reverse_iterator x = ls.rbegin(); x != ls.rend(); x++)
		{
			(*x)->OnEvent(e);
		}
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

	unsigned int Application::GetWidth()
	{
		return window->GetWidth();
	}
	
	unsigned int Application::GetHeight()
	{
		return window->GetHeight();
	}

	void* Application::GetProvider()
	{
		return window->GetProvider();
	}

	WindowProvider Application::GetProviderName()
	{
		return window->GetProviderName();
	}
	//---

}